/*
 * polygony.cpp: implementace trid pro objekty zalozene na polygonu
 */

#include <cstddef>	// NULL
#include <cmath>	// fabs()
#include <algorithm>// sort()
#include "polygony.h"

using namespace std;

// Pomocna funkce pro vypocet vektoroveho soucinu oa a ob
double vektorovy_soucin(const Bod& o, const Bod& a, const Bod& b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// Pomocna funkce pro nalezeni konvexniho obalu (v idealnim pripade je to
// polygon, ktery chtel uzivatel zadat s body v poradi proti smeru hodinovych
// rucicek.
vector<Bod> konvexni_obal(vector<Bod> body) {
	int n = body.size();
	int k = 0;
	vector<Bod> obal(2*n);

	// Seradime body podle x-ove, prip. podle y-ove souradnice
	sort(body.begin(), body.end());

	// Spodni obal
	for(int i = 0; i < n; i++) {
		while(k >= 2 && vektorovy_soucin(obal[k-2], obal[k-1], body[i]) <= 0)
			k--;
		obal[k++] = body[i];
	}
	// Vrchni obal
	for(int i = n-2, t = k+1; i >= 0; i--) {
		while(k >= t && vektorovy_soucin(obal[k-2], obal[k-1], body[i]) <= 0)
			k--;
		obal[k++] = body[i];
	}
	// Odstranit duplicitni bod ve kterem se obal uzavira
	obal.pop_back();
	// Zmensit vektor na skutecny pocet bodu obalu
	obal.resize(k - 1);
	return obal;
}

/*
 * Polygon
 */

// Zadani dalsiho bodu polygonu. Pri zadavani bodu nezalezi na poradi, pri
// praci s polygonem kvuli funkci algoritmu budeme pracovat s jeho konvexnim
// obalem (tj. jednoduchym polygonem)
void Polygon::ZadejBod(const double x, const double y) {
	this->body.push_back({x, y});
}

// Vypocet teziste polygonu (neuvazujeme zvetseni a posunuti)
Bod Polygon::VypoctiTeziste() const {
	// Pokud ma polygon mene nez 3 body, nelze spocitat plochu ani teziste.
	if(this->body.size() < 3)
		return {0, 0};

	Bod t = {0, 0};
	double s = this->VypoctiObsah();

	double faktor = 0;
	for(unsigned int i = 0; i < body.size(); i++) {
		unsigned int j = (i + 1) % body.size();

		// faktor 
		faktor = body[i].x * body[j].y - body[j].x * body[i].y;

		t.x += (body[i].x + body[j].x) * faktor;
		t.y += (body[i].y + body[j].y) * faktor;
	}

	t.x *= 1 / (s * 6);
	t.y *= 1 / (s * 6);

	return t;
}

// Vypocet obsahu polygonu (neuvazujeme zvetseni a posunuti)
double Polygon::VypoctiObsah() const {
	// Pokud ma polygon mene nez 3 body, nelze spocitat plochu.
	if(this->body.size() < 3)
		return -1;

	double s = 0;

	// Nejprve nalezneme body, ktere tvori konvexni obalku.
	vector<Bod> body = konvexni_obal(this->body);

	// Spocitame soucet vyseci vytycenych useckami
	for(unsigned int i = 0; i < body.size(); i++) {
		unsigned int j = (i + 1) % body.size();

		s += (body[i].x * body[j].y) - (body[j].x * body[i].y);
	}

	return s / 2;
}

// Vykresleni polygonu na kontext podedeny od rozhrani IKontext
void Polygon::Vykresli(IKontext *kontext) const {
	// Jen zkontrolujeme ze kontext neni NULL
	if(!kontext)
		return;

	// Pokud ma polygon mene nez 3 body, nic nevykreslime, protoze nejde o
	// mnohouhlenik.
	if(this->body.size() < 3)
		return;

	// Konvexni obal zadanych bodu
	vector<Bod> body = konvexni_obal(this->body);

	// Pro zvyseni citelnosti algoritmu nize si predgenerujeme transformace
	// bodu (posunuti a zvetseni.)
	vector<Bod> t_body;
	for(auto bod : body) {
		Bod t_bod = {bod.x, bod.y};

		// Zvetseni
		t_bod.x = (t_bod.x * this->zvetseni) 
			- (body[0].x * (this->zvetseni - 1));
		t_bod.y = (t_bod.y * this->zvetseni)
			- (body[0].y * (this->zvetseni - 1));

		// Posunuti
		t_bod.x = t_bod.x + this->posunuti.x;
		t_bod.y = t_bod.y + this->posunuti.y;

		t_body.push_back(t_bod);
	}

	// Protoze kontexty jsou bitmapa (mapa bodu) zatimco IObrazec je vektorove
	// rozhrani, musime pro vykresleni pouzit aproximacni algoritmus (navic nam
	// do toho vstupuje 'zvetseni'.) Pouzijeme Bersenhamuv algoritmus popsany
	// zde:
	// http://www.ecse.rpi.edu/~wrf/Research/Short_Notes/bresenham.html
	// Pozn.: implementace nize je optimalizovana pro vypocet odchylky v obou
	// smerech, takze nemusime mit tri vetve algoritmu.
	auto it = begin(t_body);
	while(it != end(t_body)) {
		const Bod *bod = &*it;
		// Dalsi bod, v pripade ze je posledni, nastavime ho na prvni (posledni
		// usecka polygonu aby byl uzavreny.
		const Bod *dalsi_bod = (next(it) == end(t_body)) ?
			&*(begin(t_body)) : &*(next(it));

		// Pro snazsi praci pri vykreslovani si ulozime jednotlive souradnice do
		// pomocnych promennych
		float x1 = bod->x, y1 = bod->y, x2 = dalsi_bod->x, y2 = dalsi_bod->y;

		// Prikra linka
		const bool p = (fabs(y2 - y1) > fabs(x2 - x1));
		// Jde o prikrou linku, pro jednoduchost algoritmu nize prohodime
		// souradnice (kreslime po y)
		if(p) { swap(x1, y1); swap(x2, y2); }
		// Chceme kreslit vzdy smerem doprava (dolu)
		if(x1 > x2) { swap(x1, x2); swap(y1, y2); }

		// Rozdil souradnic
		const float d_x = x2 - x1;
		const float d_y = fabs(y2 - y1);

		// Chyba od idealni usecky
		float chyba = d_x / 2;
		// Znamenko posunu po ose y (x)
		const int znam = (y1 < y2) ? 1 : -1;
		int y = y1;
		// Maximalni hodnota souradnice x
		const int max_x = x2;

		for(int x = x1; x <= max_x; x++) {
			if(p) {
				kontext->Zapis(y,x);
			} else {
				kontext->Zapis(x,y);
			}
			// Vypocet chyby od idealni usecky (kdy zalomit/prolozit)
			chyba -= d_y;
			if(chyba < 0) {
				y += znam;
				chyba += d_x;
			}
		}

		// Posunout iterator
		it++;
	}
}
