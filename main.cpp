#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#define int_to_str( x ) static_cast< ostringstream & >( \
	        ( ostringstream() << dec << x ) ).str()

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

		static void binstr_to_set(string bs) {
			// преобразуем битовую шкалу в читаемый вид
			int val = -1;
			printf(" { ");
			for (int i = bs.size() - 1; i > -1; --i) {
				val++;
				if (bs[i] == '1') {
					printf("%d ", val);;
				}
			}
			printf("}\n");
		}

		void show() {
			printf("%s = %s", name.c_str(), string_set.c_str());
			binstr_to_set(string_set);
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

string convert_to_binary(unsigned long x) {  
	int c;
	c = x % 2;
	x = x / 2;
	if (x == 0) {
		return int_to_str(c);
	}
	return convert_to_binary(x) + int_to_str(c);
}

string get_bin (string value) {
	// форматировать результат
	string base = "00000000000000000000000000000000";
	string prefix = base.substr(0, base.size() - value.size());
	return prefix + value;
}



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

	unsigned long U = create_u(A, B, C);
	
	C.inverse_set(U); // 1.

	BitScale nB ("nB", "b.txt"); // дополнительный объект для отрицания множества
	nB.inverse_set(U); // 2.
	
	C.intersect_with(nB); // 3.
	A.intersect_with(B); // 4.
	A.difference_with(C); // 5.

	string string_result = convert_to_binary(A.get_value()); // бинарное представление множества
	printf("RESULT = %s", get_bin(string_result).c_str() );
	BitScale::binstr_to_set(string_result);

	system("pause");
    return 0;
}

