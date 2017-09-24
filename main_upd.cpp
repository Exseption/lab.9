#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class BitScale {
	private:
		string string_set;
		unsigned long val;
	public:
		BitScale( string path){
			string_set = path;
		};
};


string read_file (const char* filename) { 
    // функция чтения файла с множеством (нули и единицы с пробелами)
    FILE *f = fopen(filename, "r");
    char c;
    string s; 
    if (f == NULL) { 
        printf("%s\n","File not found!");
    } else {
        while ((c = fgetc(f)) != EOF) {
            if (c != ' ') {
                s += c;
            } 
        }
    }
    fclose(f);
    return s;
};

void convert_to_binary(unsigned long n) {
	// привести десятичное число к бинарному
    if (n / 2 != 0) {
        convert_to_binary(n / 2);
    }
    printf("%ld", n % 2);
}

void show_items (string name, string value) { 
	// преобразуем битовую шкалу в читаемый вид
	int val = -1;
	int res[32], indx = 0;
	
	printf("%s = { ", name.c_str());
	for (int i = value.size() - 1; i > -1; --i)
	{
		val++;
		if (value[i] == '1') {
			indx++;
			printf("%d ", val);;
		}
	}
	printf("}\n");
}

unsigned long convert_to_number(string str) {
	// преобразовать бинарную строку в число
    char * ptr;
    unsigned long parsed = strtol(str.c_str(), & ptr, 2);
    return parsed;
}

unsigned long union_of_sets (unsigned long a, unsigned long b) {
	// объединение множеств
	return a | b;
}

unsigned long intersection_of_sets (unsigned long a, unsigned long b) {
	// пересечение множеств
	return a & b;
}

unsigned long difference_of_sets (unsigned long a, unsigned long b) {
	// разность множеств
	return a & ~b;
}

unsigned long inverse_set (unsigned long u, unsigned long a) {
	// отрицание (дополнение)
	return u & ~a;
}

unsigned long create_u (unsigned long a, unsigned long b, unsigned long c) {
	// создать универсальное множество (для отрицания множества)
	return a | b | c;
}

int main() {
	string sA, sB, sC; // строки битовых шкал
	unsigned long ulA, ulB, ulC; // числовые значения

	sA = read_file("a.txt");
	sB = read_file("b.txt");
	sC = read_file("c.txt");
	
	// выводим на экран
	printf("A = %s\n", sA.c_str());
	printf("B = %s\n", sB.c_str());
	printf("C = %s\n", sC.c_str());
	
	ulA = convert_to_number(sA);
	show_items("A", sA);

	ulB = convert_to_number(sB);
	show_items("B", sB);

	ulC = convert_to_number(sC);
	show_items("C", sC);

	unsigned long ab = union_of_sets(ulA, ulB);
    
    // 9. A ∩ B \ -(C U B) задача
    //   (A & B) & ~(~C & ~B)
    // A = {0, 1, 17, 30}
    // B = {3, 7 , 30}
    // C = {1, 20, 31}

    /* Порядок действий:
    1. Отрицание С
    2. Отрицание В
    3. Пересечение -С и -В
    4. Пересение A и B
    5. Разность (4) и (3)
	*/

	unsigned long U = create_u(ulA, ulB, ulC);
	unsigned long neg_c = inverse_set(U, ulC);
	unsigned long neg_b = inverse_set(U, ulB);
	unsigned long CB = intersection_of_sets(neg_c, neg_b);
	unsigned long AB = intersection_of_sets(ulA, ulB);
	unsigned long result = difference_of_sets(AB, CB);
	
	printf("\n");

    return 0;
}

