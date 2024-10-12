#include <iostream>
#include <fstream>
#include <string>


using namespace std;
const int N = 50;

struct tabla {
    int puntos[N];
    int rachas[N];
    string nombres[N];
    string ultimaVictoria[N];
    int n = 0;
};

int esta(string nombre, tabla t) {
    int res = -1;
    for (int i = 0; i < t.n; i++) {
        if (t.nombres[i] == nombre) {
            res = i;
            break;
        }
    }
    return res;
}

bool poneResultado (string l) {
	if (l.length() != 9) {
		return false;
	}
	string aux = "RESULTADO";
	for (int i = 0; i < l.length(); i ++) {
		aux[i] = tolower(l[i]);
	}
	return aux == "resultado";
}

int main() {
    tabla puntuaciones;
    cout << "Nombre del fichero a leer: ";
    string fLectura;
    cin >> fLectura;
    ifstream lectura(fLectura);
    ifstream antRes("resultados.csv");
	ofstream lineasMal("lineasRevision.txt");
	
    if (!lectura.is_open()) {
        cerr << "Error al leer el fichero de datos \"" << fLectura << "\"." << endl;
        return 1;
    }
	if (!lineasMal.is_open()) {
		 cerr << "Error al abrir el fichero de lineas para revision" << endl;
		 return 1;
	}
    string l;
    if (antRes.is_open()) {
        while (getline(antRes, l, ';')) {
            puntuaciones.nombres[puntuaciones.n] = l;
			//cout << l << ": ";
            getline(antRes,l,';');
            puntuaciones.puntos[puntuaciones.n] = stoi(l);
			getline(antRes,l,';');
            puntuaciones.rachas[puntuaciones.n] = stoi(l);
            getline(antRes,l);
            puntuaciones.ultimaVictoria[puntuaciones.n] = l;
            puntuaciones.n++;
			//cout << l << endl;
        }
        antRes.close();
    }
    ofstream escritura("resultados.csv");
	if (!escritura.is_open()) {
		 cerr << "Error al abrir el fichero de escritura" << endl;
		return 1;
	}
    while (getline(lectura, l, ' ')) {
		string lineaRevision = l + ' ';
        if (!poneResultado(l)) {
            getline(lectura,l);
           continue;
        }
		bool alguienEsGilipollas = false;
		getline(lectura, l, '@');
		lineaRevision += l + '@';
		if (l.find('(', 0) != -1) {
			alguienEsGilipollas = true;
		}
        getline(lectura, l, '(');
		lineaRevision += l + '(';
		while (l.back() == ' ') {
			l.pop_back();
		}
		int pos1 = esta(l, puntuaciones);
        string n1 = l;
		if (!alguienEsGilipollas) {
			getline(lectura, l, '(');
			lineaRevision += l + '(';
		}
        getline(lectura, l, '-');
		bool taBien = true;
		for (int i = 0; i < l.length(); i++) {
			if (isdigit(l[i]) == 0) {
				taBien = false;
				break;
			}
		}
		int p1;
		if (taBien) {
			p1 = stoi(l);
			lineaRevision += l + '-';
		}
		else {
			cerr << "linea erronea" << endl;
			getline(lectura, l);
			lineaRevision += l;
			lineasMal << lineaRevision << endl;
			continue;
		}
		getline(lectura, l, ')');
		for (int i = 0; i < l.length(); i++) {
			if (isdigit(l[i]) == 0) {
				taBien = false;
				break;
			}
		}
		int p2;
		if (taBien) {
			p2 = stoi(l);
			lineaRevision += l + ')';
		}
		else {
			cerr << "linea erronea" << endl;
			getline(lectura, l);
			lineaRevision += l;
			lineasMal << lineaRevision << endl;
			continue;
		}
        getline(lectura, l, '@');
		getline(lectura, l);
		int posParentesis = l.find('(', 0);
		if (posParentesis != -1) {
			l = l.substr(0, posParentesis);
		}
		while (l.back() == ' ') {
			l.pop_back();
		}
        int pos2 = esta(l, puntuaciones);
        string n2 = l;
        int puntos1 = p1-p2;
        int puntos2 = p2-p1;
		//cout << p1 << " " << p2 << " " << puntos1 << " " << puntos2 << endl;
		
		
		
        if (pos1 == -1 && pos2 == -1) {
            puntuaciones.nombres[puntuaciones.n] = n1;
            pos1 = puntuaciones.n;
            puntuaciones.n++;
            puntuaciones.nombres[puntuaciones.n] = n2;
            pos2 = puntuaciones.n;
            puntuaciones.n++;
                
            puntuaciones.puntos[pos1] = puntos1;
            puntuaciones.puntos[pos2] = puntos2;
			//cout << "if 1, p1 = " << puntos1 << ", p2 = " << puntos2 << endl;
            if (puntos1 > puntos2) {
                puntuaciones.rachas[pos1] = 1;
                puntuaciones.rachas[pos2] = 0;
                puntuaciones.ultimaVictoria[pos1] = n2;
                puntuaciones.ultimaVictoria[pos2] = "";
            } else {
                puntuaciones.rachas[pos1] = 0;
                puntuaciones.rachas[pos2] = 1;
                puntuaciones.ultimaVictoria[pos2] = n1;
                puntuaciones.ultimaVictoria[pos1] = "";
            }
        }
        else if (pos1 == -1 && pos2 != -1) {
            puntuaciones.nombres[puntuaciones.n] = n1;
            pos1 = puntuaciones.n;
            puntuaciones.n++;
			if (puntuaciones.puntos[pos1] >= puntuaciones.puntos[pos2] + 10) {
                puntos2++;
                puntos1--;
            } else if (puntuaciones.puntos[pos2] >= puntuaciones.puntos[pos1] + 10) {
                puntos1++;
				puntos2--;
            }
            if (puntos2 > puntos1) {
				//cout << "if 2, p1 = " << puntos1 << ", p2 = " << puntos2 << endl;
                puntuaciones.puntos[pos1] = puntos1;
                puntuaciones.puntos[pos2] += puntos2;
				puntuaciones.rachas[pos1] = 0;
				if (puntuaciones.ultimaVictoria[pos2] != puntuaciones.nombres[pos1]) {
					puntuaciones.rachas[pos2]++;
					if (puntuaciones.rachas[pos2] % 5 == 0) {
						puntuaciones.puntos[pos2] +=5;
					}
				}
                puntuaciones.ultimaVictoria[pos2] = n1;
                puntuaciones.ultimaVictoria[pos1] = "";
            } else {
				//cout << "if 2, p1 = " << puntos1 << ", p2 = " << puntos2 << endl;
				puntuaciones.puntos[pos1] = puntos1;
				puntuaciones.puntos[pos2] += puntos2;
                puntuaciones.rachas[pos1] = 1;
                if (puntuaciones.rachas[pos2] >= 5) {
                    puntuaciones.puntos[pos1] += 5;
                }
                puntuaciones.rachas[pos2] = 0;
                puntuaciones.ultimaVictoria[pos1] = n2;
                puntuaciones.ultimaVictoria[pos2] = "";
            }
        }
        else if (pos2 == -1 && pos1 != -1) {
            puntuaciones.nombres[puntuaciones.n] = n2;
            pos2 = puntuaciones.n;
            puntuaciones.n++;
			if (puntuaciones.puntos[pos1] >= puntuaciones.puntos[pos2] + 10) {
                puntos2++;
                puntos1--;
            } else if (puntuaciones.puntos[pos2] >= puntuaciones.puntos[pos1] + 10) {
                puntos1++;
				puntos2--;
            }
            if (puntos1 > puntos2) {
				//cout << "if 3, p1 = " << puntos1 << ", p2 = " << puntos2 << endl;
                puntuaciones.puntos[pos1] += puntos1;
                puntuaciones.puntos[pos2] = puntos2;
				puntuaciones.rachas[pos2] = 0;
				if (puntuaciones.ultimaVictoria[pos1] != puntuaciones.nombres[pos2]) {
					puntuaciones.rachas[pos1]++;
					if (puntuaciones.rachas[pos1] % 5 == 0) {
						puntuaciones.puntos[pos1] +=5;
					}
				}
                puntuaciones.ultimaVictoria[pos1] = n2;
                puntuaciones.ultimaVictoria[pos2] = "";
            } else {
				//cout << "if 3, p1 = " << puntos1 << ", p2 = " << puntos2 << endl;
                puntuaciones.puntos[pos2] += puntos1;
                puntuaciones.puntos[pos1] = puntos2;
                puntuaciones.rachas[pos2] = 1;
                if (puntuaciones.rachas[pos1] >= 5) {
                    puntuaciones.puntos[pos2] += 5;
                }
                puntuaciones.rachas[pos1] = 0;
                puntuaciones.ultimaVictoria[pos2] = n1;
                puntuaciones.ultimaVictoria[pos1] = "";
            }
        }
        else {
			if (puntuaciones.puntos[pos1] >= puntuaciones.puntos[pos2] + 10) {
                puntos2++;
                puntos1--;
            } else if (puntuaciones.puntos[pos2] >= puntuaciones.puntos[pos1] + 10) {
                puntos1++;
				puntos2--;
            }
            if (puntos1 > puntos2) {
				if (puntuaciones.ultimaVictoria[pos1] != puntuaciones.nombres[pos2]) {
					puntuaciones.rachas[pos1]++;
					if (puntuaciones.rachas[pos1] % 5 == 0) {
						puntuaciones.puntos[pos1] += 5;
					}
					if (puntuaciones.rachas[pos2] >= 5) {
						puntuaciones.puntos[pos1] += 5;
					}
					puntuaciones.rachas[pos2] = 0;
				}
                puntuaciones.ultimaVictoria[pos1] = n2;
                puntuaciones.ultimaVictoria[pos2] = "";
            } else {
				if (puntuaciones.ultimaVictoria[pos2] != puntuaciones.nombres[pos1]) {
					puntuaciones.rachas[pos2]++;
					if (puntuaciones.rachas[pos2] % 5 == 0) {
						puntuaciones.puntos[pos2] += 5;
					}
					if (puntuaciones.rachas[pos1] >= 5) {
						puntuaciones.puntos[pos2] += 5;
					}
					puntuaciones.rachas[pos1] = 0;
				}
                puntuaciones.ultimaVictoria[pos2] = n1;
                puntuaciones.ultimaVictoria[pos1] = "";
            }
			//cout << "if 4, p1 = " << puntos1 << ", p2 = " << puntos2 << endl;
            puntuaciones.puntos[pos1] += puntos1;
            puntuaciones.puntos[pos2] += puntos2;
        }
    }
    for (int i = 0; i < puntuaciones.n; i++) {
        escritura << puntuaciones.nombres[i] << ";"
                  << puntuaciones.puntos[i] << ";"
                  << puntuaciones.rachas[i] << ";"
				  << puntuaciones.ultimaVictoria[i]
                  << endl;
    }
    lectura.close();
    escritura.close();
	lineasMal.close();
}