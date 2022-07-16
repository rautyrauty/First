#include <iostream> // поток ввода и вывода через клаву
#include <fstream> // поток ввода и вывода через файлы
#include <vector> // динамический массив вектор
#include <iomanip> // фишки с потоками вывода и ввода
#include <string> // фишки со строками
#include <sstream> // поток строк
#include <cmath> // фишки с матеши
#include <ctime> // фишки с временем
#include <cassert>// фишки с временем
// использование пространства имён std:
using namespace std;
// Поразрядная сортировка и Поиск максимального элемента статического массива. Лекция 8
int max_of_array(const int* A, const int& N)
{
	int max = -1;
	for (int i = 0; i < N; i++)
	{
		if (A[i] > max) max = A[i];
	}
	return max;
}
void bitwise_sort(int* A, const int& N, const int& max)
{
	vector<int> zero; vector<int> one;
	for (int j = 0; (max / int(pow(2, j))) > 0; j++)
	{
		for (int i = 0; i < N; i++) {
			if ((A[i] / int(pow(2, j))) % 2 == 0) zero.push_back(A[i]);
			if ((A[i] / int(pow(2, j))) % 2 == 1)
			{
				one.push_back(A[i]);
			}
		}
		for (int i = 0; i < zero.size(); i++) A[i] = zero[i];
		for (int i = zero.size(); i < N; i++) A[i] = one[i - zero.size()];
		zero.clear(); one.clear();
	}
}
/*int main() // Пример работы
{
	const int N = 10;
	int A[N] = { 10,9,8,1000,6,15,4,3,2,100 };
	bitwise_sort(reinterpret_cast<int*>(A), N, max_of_array(reinterpret_cast<int*>(A), N));
	for (int i = 0; i < N; i++) cout << A[i] << '\t';
	cout << '\n';
	return 0; // АХАХААХАХАХАХХАХАХАХАХА ОНО РАБОТАЕТ!!!!
}*/
// Приколы с двоичными динамическими массивами.
void print_and_fill_array_2d(const int N, const int M, int* A)
{
	int k = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			*(A + j + M * i) = k++;
			cout << *(A + j + M * i) << '\t';
		}
		cout << '\n';
	}
}
//Выше идут лекции с МФТИ
// Рекурсивные сортировки слиянием и Тони Хоара("Быстрая"). Урок 23
void quick_sort_merge(const vector<int>& left, const vector<int>& right, const vector<int>& middlev, vector<int>& A)
{
	vector<int>::size_type k = 0;
	for (vector<int>::size_type i = 0; i < left.size(); i++) A[k++] = left[i];
	for (vector<int>::size_type i = 0; i < middlev.size(); i++) A[k++] = middlev[i];
	for (vector<int>::size_type i = 0; i < right.size(); i++) A[k++] = right[i];
}
void quick_sort(vector<int>& A)
{
	if (A.size() <= 1) return;
	int middle = A[0];
	vector<int> left; vector<int> right; vector<int> middlev;
	for (vector<int>::size_type i = 0; i < A.size(); i++)
	{
		if (A[i] < middle) {
			left.push_back(A[i]); 
			continue;
		}
		if (A[i] > middle) {
			right.push_back(A[i]);
			continue;
		}
		middlev.push_back(A[i]);
	}
	quick_sort(left); quick_sort(right);
	quick_sort_merge(left, right, middlev, A);
}
void merge_sorted_vectors(const vector<int>& A, const vector<int>& B, vector<int>& C) // Слияние двух отсортированных массивов
{
	size_t i = 0, k = 0, n = 0;
	while (i<A.size() and k<B.size())
	{
		if (A[i] <= B[k]) C[n++] = A[i++];
		else  C[n++] = B[k++];
	}
	while (i < A.size()) C[n++] = A[i++];
	while (k < B.size()) C[n++] = B[k++];
}
void merge_sort(vector<int>& A) // Сортировка слиянием
{
	if (int(A.size()) > 1)
	{
		int N = A.size();
		vector<int> left; vector<int> right;
		for (int i = 0; i < N / 2; i++) left.push_back(A[i]);
		for (int i = N / 2; i < N; i++) right.push_back(A[i]);
		merge_sort(left); merge_sort(right);
		merge_sorted_vectors(left, right, A);
	}
}
// Быстрое возведение в степень через Рекурсию. Урок 22
int my_pow(int a, int n)
{
	if (n == 0) return 1;
	if (n % 2 == 0) return (my_pow(a * a, n / 2));
	return my_pow(a, n - 1)*a; // делаем четной
}
// Нахождение НОД через Рекурсию (алгоритм Евклида). Урок 22
int gcd_evclid_1(int a, int b)
{
	if (a == b) return a;
	if (a > b) return gcd_evclid_1(a - b, b);
	return gcd_evclid_1(a, b - a);
}
int gcd_evclid_2(int a, int b) // продвинутый алг.
{
	assert(a > b);
	if (b == 0) return a;
	return (b, a % b); //усливие, что 
}
// Генератор чисел через Рекурсию. Урок 22
void num_generator(int num_system, int lenght, vector<int>& digits)
{
	if (lenght == 0) {
		for (int i = 0; i< int(digits.size()); i++) cout << digits[i];
		cout << '\n';
	}
	else {
		for (int k = 0; k < num_system; k++) {
			digits.push_back(k);
			num_generator(num_system, lenght - 1, digits);
			digits.pop_back();
		}
	}
}
// Задача с Ханойскими башнями (Рекурсия). Урок 21
void towers_of_hanoi(int n, int start, int finish)
{
	if (n == 1) { // крайний случай
		cout << "Move disk " << n << " from " <<
			start << " to " << finish << '\n';
	}
	else { // рекуррентный случай
		int tmp = 6 - start - finish;
		towers_of_hanoi(n - 1, start, tmp);
		cout << "Move disk " << n << " from " <<
			start << " to " << finish << '\n';
		towers_of_hanoi(n - 1, tmp, finish);
	}
}
// Структура данных - Пирамида (Куча). Урок 20
typedef int pyramidData_t; // для обозначения типа(type) данных пирамиды
typedef vector<pyramidData_t> pyramid_t; // для обозначения типа пирамиды
vector<int> vector_random_generator(int Size) // Генератор рандомного не сортированного вектора
{
	vector<int> A(Size);
	for (int i = 0; i < Size; i++) 
	{
		int x = rand();
		x %= 10000; // здесь настраивать диапозон
		A[i] = x;
	}
	return A;
}
int pyramid_height(const pyramid_t& p) // Возвращает высоту пирамиды
{
	int h = 0;
	for (int i = p.size(); i > 0;)
	{
		for (int z = pow(2, h); (z > 0) and (i > 0); z--) i--;
		h++;
	}
	return h;
}
void print_pyramid(const pyramid_t& p) // Печатает пирамиду
{
	int degree = 0;
	pyramid_t::size_type i = 0;
	cout << '\n';
	for (int h = pyramid_height(p); h > 0; h--)
	{
		for (int counter = h; counter > 0; counter--) cout << "   ";
		for (int counter = pow(2, degree++); counter > 0; counter--)
		{
			cout << p[i] << "  "; i++;
			if (i >= p.size()) break;
		}
		cout << '\n';
	}
}
bool pyramid_sorted(const pyramid_t& p) // Если пирамида отсортирована - 1, если нет - 0
{
	pyramid_t::size_type i = p.size() - 1;
	i = (i - 1) / 2;
	if (2 * i + 2 >= p.size())
	{
		if (p[2 * i + 1] > p[i]) return 0;
		i--;
	}
	pyramid_t::size_type left, right;
	for (; ; i--)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		if ((p[i] < p[left]) or (p[i] < p[right])) return 0;
		if (i == 0) break;
	}
	return 1;
}
void pyramid_sorting_attempt(pyramid_t& p) // Проход сортировки пирамиды
{
	pyramid_t::size_type i = p.size() - 1;
	i = (i - 1) / 2;
	if (2 * i + 2 >= p.size())
	{
		if (p[2 * i + 1] > p[i]) swap(p[2 * i + 1], p[i]);
		i--;
	}
	pyramid_t::size_type max, left, right;
	for (; ; i--)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		if (p[left] > p[right]) max = left;
		else max = right;
		if (p[max] > p[i]) swap(p[max], p[i]);
		if (i == 0) break;
	}
}
pyramidData_t take_out_top(pyramid_t& p) // Возвращает вырезанное значение вершины пирамиды и автоматически сортирует её
{
	pyramidData_t top = p[0];
	swap(p[0], p[p.size() - 1]); p.pop_back();
	pyramid_t::size_type max, left, right;
	for (pyramid_t::size_type i = 0; i < p.size();)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		if (left >= p.size()) break;
		if ((right >= p.size()) or (p[left] > p[right])) max = left;
		else max = right;
		if (p[max] < p[i]) break;
		swap(p[max], p[i]);
		i = max;
	}
	return top;
}
void put_in_pyramid(pyramid_t& p, pyramidData_t x) // Вставляет в пирамиду значение
{
	p.push_back(x);
	for (pyramid_t::size_type i = p.size() - 1; (i > 0) and (p[i] > p[(i - 1) / 2]); i = (i - 1) / 2)
	{
		swap(p[i], p[(i - 1) / 2]);
	}
}
void print_top_of_pyramid(const pyramid_t& p) // Печатает максимальное число в пирамиде
{
	cout << "Top of the pyramid = " << p[0] << '\n';
}
// Олимпиадная задача с сортировкой. Домашнее задание. Урок 18
void olympiad_task(vector<int>& A)
{
	for (int pos = 1; pos < int(A.size()); pos++)
	{
		if (A[pos] == 0) continue;
		int k = 1;
		for (int i = pos; i - k >= 0; k++)
		{
			if (A[i - k] * A[i] <= 0) continue;
			if (A[i] < A[i - k]) {
				swap(A[i], A[i - k]);
				i -= k; k = 0;
			}
			else break;
		} // -1000 50 -2132 0 -323 4332 344 -21 0  -312 -1444 -2324 3443 0 -3242 43 2342 434 0 432 322 4342 -324 432
	}
}
// Сортировка подсчетом моя(плохая) и учителя(крутая). Урок 17
void Airat_count_sort_10(vector<int>& A) // Легкая сортировка, описание не требуется
{
	vector<int> C(10);
	for (int i = 0; i < int(A.size()); i++) {
		if (A[i] < 0 or A[i]>9) {
			cerr << "CAN'T SORT NOT DIGITS VALUES!\n";
			exit(-1);
		}
		C[A[i]]++;
	}
	int i = 0;
	for (int pos = 0; pos < int(A.size()); pos++) {
		while (C[i] == 0) i++;
		A[pos] = i; C[i]--;
	}
}
void Timofey_count_sort_10(vector<int>& A)
{
	vector<int> C(10);
	for (int i = 0; i < int(A.size()); i++)
	{
		if (A[i] < 0 or A[i]>9)
		{
			cerr << "CAN'T SORT NOT DIGITS VALUES!\n";
			exit(-1);
		}
		C[A[i]]++;
	}
	int n = 0;
	for (int x = 0; x < 10; x++)
		for (int i = 0; i < C[x]; i++)
			A[n++] = x;
}
// Сортировка выборная и сортировка вставками. Урок 16
void insert_sort(vector<int>& A) // Сортировка вставками. Имба лютейшая!
{
	for (int pos = 1; pos < int(A.size()); pos++)
		for (int i = pos; (i > 0) and (A[i] < A[i - 1]); i--) swap(A[i], A[i - 1]);
	// Сортировка вставками предполагает собой взятие нового элемента и его вставка в отсортированный массив
}
void selection_sort(vector<int>& A) // Выборная сортировка. Под пиво сойдёт
{
	for (int pos = 0; pos < int(A.size()) - 1; pos++)
	{
		int min_num = pos; bool f = 1;
		for (int tmp = pos + 1; tmp < int(A.size()); tmp++)
		{
			if (A[tmp] < A[min_num]) { min_num = tmp; f = 0; }
		}
		if (not f) swap(A[pos], A[min_num]);
	}
	// Выборная сортировка предполагает собой поочерёдное нахождение минимума в массиве
}
// Поток ввода строки, сортировка дурака и пузырьком. Урок 15
vector<int> input_vector() // Заполнение вектора через поток строки введённого пользователем
{
	string line; getline(cin, line);
	stringstream line_stream(line);
	vector<int> A;
	while (not line_stream.eof()) {
		int x; line_stream >> x;
		A.push_back(x);
	}
	return A; // нужно что-то типо написать vector<int> array = input_vector()
}
bool is_ascending_order(const vector<int>& A) // Проверка стоят ли числа в порядке возрастания
{
	for (int i = 0; i < int(A.size()) - 1; i++)
	{
		if (A[i] > A[i + 1]) {
			return false;
		}
	}
	return true;
}
void fool_sort(vector<int>& A) // Сортировка дурака
{
	for (int i = 0; i < int(A.size()) - 1; i++)
	{
		if (A[i] > A[i + 1]) {
			swap(A[i], A[i + 1]);
			i = -1;
			continue;
		}
	}
	// Сортировка дурака предпологает собой проверку, замену неправильно стоящих элементов и так по кругу
}
void bubble_sort(vector<int>& A) // Умная сортировка пузырьком
{
	bool sorted_flag = 0;
	for (int bypass_counter = 0; not sorted_flag; bypass_counter++)
	{
		sorted_flag = 1;
		for (int i = 0; i < int(A.size()) - 1 - bypass_counter; i++)
		{
			if (A[i] > A[i + 1]) {
				swap(A[i], A[i + 1]);
				sorted_flag = 0;
			}
		}
	}
	// Сортировка пузырьком почти то же самое, что и сортировка дурака
	// только после  нахождения непорядка она продолжает поиск и замену
	// Таким образом постоянно выводя в левую часть массива самые большие элементы. Как пузырёк ыыыыыы.
}
// Бинарный поиск границ в массиве
typedef double T; // T = double
int left_boundary(T x, const vector<T>& A)
{
	int left = 0;
	while (left < int(A.size()) and A[left] < x) left++;
	return left;
}
int right_boundary(T x, const vector<T>& A)
{
	int right = int(A.size())-1;
	while (right > 0 and A[right] > x) right--;
	return right;
}
int binleft_boundary(T x, const vector<T>& A)
{
	int l = 0, r = int(A.size())-1;
	while (r - l > 1)
	{
		int middle = (r + l) / 2;
		if (middle >= x) r = middle;
		else l = middle;
	}
	return l;
}
int binright_boundary(T x, const vector<T>& A)
{
	int l = 0, r = int(A.size()) - 1;
	while (r - l > 1)
	{
		int middle = (r + l) / 2;
		if (middle <= x) l = middle;
		else r = middle;
	}
	return r;
}
void binSearch_for_boundaries_in_vector()
{
	T x; vector<T> A = { 2,2,2,3,3,3,5,5,5,5,5,6,7,7,9,9 }; // Объявление значения для поиска и массива для поиска
	cout << "What to find? x = "; cin >> x;
	int left = left_boundary(x, A); int right = right_boundary(x, A);
	cout << "Noob finder give answer: "
		 << '[' << left << ';' << right << ']' << '\n';
	int binleft = binleft_boundary(x, A); int binright = binright_boundary(x, A);
	cout << "Binsearch finder give answer: "
		<< '[' << left << ';' << right << ']' << '\n';
}
//Бинарный поиск корня в функции f(x)
double f(double x)
{
	return (x - 2.21313) * (x - 7);
}
void binSearch_root()
{
	double a, b; cout << "Enter boundaries [a,b]: "; cin >> a >> b;
	double ERROR; cout << "Enter error: "; cin >> ERROR;
	if (f(a) * f(b) < 0) {
		while ((b - a) / 2. > ERROR) {
			double c = (a + b) / 2;
			if (f(c) == 0) {
				cout << "OMG!!! 1001% answer is: " << c << '\n';
			}
			if (f(a) * f(c) <= 0) b = c;
			else a = c;
		}
		cout << "Answer is: " << setprecision(17) << (a + b) / 2 << '\n';
	}
	else { cout << "Cant use binsearch of root bcs f(a) * f(b) >= 0\n"; }
}
//Действия с массивом
void print_vector(const vector<int>& A) // распечатка вектора
{
	for (int x = 0; x < int(A.size()); x++) cout << A[x] << ' ';
	cout << '\n';
}
void shift_right(vector<int>& A)
{
	int x = A[A.size()-1];
	for (int i =int(A.size()) - 1; i > 0; i--)
	{
		A[i] = A[i - 1];
	}
	A[0] = x;
}
void shift_left(vector<int>& A)
{
	int x = A[0];
	for (int i = 0; i < int(A.size())-1; i++)
	{
		A[i] = A[i + 1];
	}
	A[A.size()-1] = x;
}
void reverse(vector<int>& A)
{
	int N = int(A.size());
	for (int i = 0; i <= N/2; i++)
	{
		int x = A[i];
		A[i] = A[N - i - 1];
		A[N - i - 1] = x;
	}
}
//Решение 27 задачи ЕГЭ змейкой
void zmeyka27() {
	const int Q_size = 5;
	int Q[Q_size];
	for (int i = 0; i < Q_size; i++)
	{
		cin >> Q[i];
	}
	int Q_end = 0, max_from_before = -1, N = 15, max_sum = -1;
	for (int i = Q_size; i < N; i++)
	{
		int current, number_leaving_queue = Q[Q_end];
		cin >> current;
		Q[Q_end++] = current;
		if (max_sum < current + max_from_before) max_sum = current + max_from_before;
		if (Q_end == Q_size) Q_end = 0;
		if (number_leaving_queue > max_from_before) max_from_before = number_leaving_queue;
	}
	cout << max_sum << '\n';
}
//Попытка в структуры и оператор
//задача с нахождением ЛЮДЕЙ с максимальным количеством возрастов
struct Person {
	int age = 0;
	string name;
};
ostream& operator << (ostream& out, Person& one) {
	out << '[' << one.name << ']';
	return out;
}
void poisk()
{
	int N; cin >> N;
	vector<int> ages_count(101);
	vector<Person> crowd(N);
	for (int i = 0; i < N; i++)
	{
		Person one;
		cin >> one.name >> one.age;
		crowd[i] = one;
		ages_count[one.age]++;
	}
	int max_count = -1, max_age=0;
	for (int i = 0; i < 101; i++)
	{
		if (ages_count[i] > max_count) {
			max_count = ages_count[i];
			max_age = i;
		}
		//cout << ages_count[i] << '\n';
	}
	for (int i = 0; i < N; i++) {
		if (crowd[i].age == max_age) cout << crowd[i] << '\n';
	}
}
//Проверка на правильность написания разных видов скобок в матем. варажении. Использование СТЕК'а
void skobki()
{
	string a; vector<char> A(10);int THE_END = 0; 
	cout << "Enter the virajenie: ";cin >> a; 
	bool f = 1;
	for (int i = 0; a[i] != '\0'; i++)
	{
		switch (a[i])
		{
		case '[':
			A[THE_END++] = a[i];
			break;
		case '(':
			A[THE_END++] = a[i];
			break;
		case '{':
			A[THE_END++] = a[i];
			break;
		case ')':
			if (A[THE_END - 1] == '(') { A[--THE_END] = '0'; }
			else { f = 0; }
			break;
		case ']':
			if (A[THE_END - 1] == '[') {A[--THE_END] = '0';}
			else { f = 0; }
			break;
		case '}':
			if (A[THE_END - 1] == '[') { A[--THE_END] = '0'; }
			else { f = 0; }
			break;
		default:
			break;
		}
		if (f == 0) {
			cout << "\nERROR SYNTAX ";
			break;
		}
	}
	if (THE_END != 0) { cout << "ERROR\n"; }
	else { cout << "\nCORRECT\n"; }
}
int main()
{
	return 0;
}
