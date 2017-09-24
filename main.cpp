#include <stdio.h>
#include <bitset>
#include <iostream>

using namespace std;

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


void to_numbers (string name, string bs) { 
	// преобразуем битовую шкалу в читаемый вид
	int counter = -1;

    cout << name << " = "<< bs << " ( ";
	for (int i = bs.size() - 1; i > -1; --i)
	{
		counter++;
		if (bs[i] == '1') {
			cout << counter << " ";
		}
	}
	cout << ")" << endl;
}


int main(int argc, char **argv) {
    // создаем bitset на 32 бита и храним в нем множество А из файла а
    // работаем с битовыми шкалами, числа читаются справа налево
    bitset <32> A (read_file("a.txt")); 
    to_numbers("A", A.to_string()); 

    bitset <32> B (read_file("b.txt")); // В из в
    to_numbers("B", B.to_string());

    bitset <32> C (read_file("c.txt")); // C из с
    to_numbers("C", C.to_string());

    // 9. A ∩ B \ -(C U B) задача
    //   (A & B) & ~(~C & ~B)
    // A = {0, 1, 17, 30}
    // B = {3, 7 , 30}
    // C = {1, 20, 31}

    // Ненужные комменты удалить

    /* Объединение, пересечение, разность, отрицание множеств с помощью bitset 
    представляются битовыми операциями |, &, &~, ~
    Немного подзабыл теорию множеств, но
    отрицание множества, как понимаю, дополнение его до универсального.
    Универсальное множество здесь то, что содержит элементы всех 
    трех множеств за исключением своих 
    (или все эелементы выбранного диапазона 32 бита, 
    но результат получается так же верным)
    отрицание дизъюнкции = конъюнкция отрицаний множеств. 
    
    Результат с текущими множествами 01000000000000000000000000000000 (30), 
    проверил через LaTeX, совпадает */

    bitset <32> AB (A | B);
    cout << AB << endl;

    // bitset <32> U (A | B | C); // универсальное множество
    // bitset <32> R = ((A & B) & ~((U & ~C) & (U & ~B)));
    // to_numbers("RESULT", R.to_string());
    return 0;
}





