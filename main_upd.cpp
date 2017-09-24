#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class BitScale {
	private:
		string name;
		string string_set;
		unsigned long value;
	public:
		BitScale(string _name, const char * path) {
			name = _name;
			FILE *f = fopen(path, "r");
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
			string_set = s;
			// преобразовать бинарную строку в число
		    char * ptr;
		    value = strtol(string_set.c_str(), & ptr, 2);
		}

		BitScale (string _name, unsigned long _val) {
			name = _name;
			value = _val;
		}

		void show() {
			printf("%s = %s", name.c_str(), string_set.c_str());
					// преобразуем битовую шкалу в читаемый вид
			int val = -1;
			printf(" { ");
			for (int i = string_set.size() - 1; i > -1; --i) {
				val++;
				if (string_set[i] == '1') {
					printf("%d ", val);;
				}
			}
			printf("}\n");
		}

		unsigned long get_value () {
			return value;
		}

		void union_with (BitScale another) {
			// объединение множеств
			value |= another.get_value();
		}

		void intersect_with (BitScale another) {
			// пересечение множеств
			value &= another.get_value();
		}

		void difference_with (BitScale another) {
			// разность множеств
			value = value & ~another.get_value();
		}

		void inverse_set (unsigned long u) {
			// отрицание (дополнение)
			value =  u & ~value;
		}
};
		
unsigned long create_u (BitScale a, BitScale b, BitScale c) {
	// создать универсальное множество (для отрицания множества)
	return a.get_value() | b.get_value() | c.get_value();
}

void convert_to_binary(unsigned long n) {
	// привести десятичное число к бинарному
    if (n / 2 != 0) {
        convert_to_binary(n / 2);
    }
    printf("%ld", n % 2);
}



class BitScaleManipulator {
	public:
		unsigned long union_of_sets (BitScale a, BitScale b) {
			// объединение множеств
			return a.get_value() | b.get_value();
		}

		unsigned long intersection_of_sets (BitScale a, BitScale b) {
			// пересечение множеств
			return a.get_value() & b.get_value();
		}

		unsigned long difference_of_sets (BitScale a, BitScale b) {
			// разность множеств
			return a.get_value() & ~b.get_value();
		}

		unsigned long inverse_set (unsigned long u, BitScale a) {
			// отрицание (дополнение)
			return u & ~(a.get_value());
		}

		unsigned long create_u (BitScale a, BitScale b, BitScale c) {
			// создать универсальное множество (для отрицания множества)
			return a.get_value() | b.get_value() | c.get_value();
		}

		void convert_to_binary(unsigned long n) {
			// привести десятичное число к бинарному
		    if (n / 2 != 0) {
		        convert_to_binary(n / 2);
		    }
		    printf("%ld", n % 2);
		}
};

int main() {
	BitScale A ("A", "a.txt");
	BitScale B ("B", "b.txt");
	BitScale C ("C", "c.txt");

	A.show();
	B.show();
	C.show();
    
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

	BitScaleManipulator bsManipulator;
	unsigned long U = bsManipulator.create_u(A, B, C);
	BitScale neg_c ("Negative C", bsManipulator.inverse_set(U, C));
	BitScale neg_b ("Negative B", bsManipulator.inverse_set(U, B));
	BitScale CB ("CB", bsManipulator.intersection_of_sets(neg_c, neg_b));
	BitScale AB ("AB", bsManipulator.intersection_of_sets(A, B));
	unsigned long result = bsManipulator.difference_of_sets(AB, CB);
	
	// printf("%ld\n", result);
	printf("RESULT = ");
	bsManipulator.convert_to_binary(result);
	printf("\n");
    return 0;
}

