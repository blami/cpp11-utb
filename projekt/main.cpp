/*
 * skola.cpp: hlavni zdrojovy soubor s funkci main
 */

#include <iostream>
#include "databaze.h"
#include "menu.h"

using namespace std;


int main() {
	auto databaze = make_shared<data::Databaze>();
	auto menu = menu::Menu(databaze);

	// Spustit aplikaci
	menu.Spust();
}
