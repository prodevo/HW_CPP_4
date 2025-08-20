#include <iostream>
#include <windows.h>
#include <algorithm>
using namespace std;

class Vector {
	unsigned int capacity = 10; // при створенні масиву, він одразу для себе робить запас пам'яті на 10 елементів
	int* data = new int[capacity];
	unsigned int length = 0; // фактична (реальна) кількість елементів, присутніх у масиві

public:
	Vector() {}

	void AddToBack(int value) {
		if (length < capacity) // якщо виділенної зарання пам'яті ВИСТАЧАЄ для додавання чергового елемента
			data[length] = value;
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			// в новий масив в кінець (по індексу 10) пишеться ОДИНАДЦЯТИЙ елемент
			temp[length] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void AddToFront(int value) {
		if (length < capacity) { // ще є вільна пам'ять під черговий елмент
			// перевиділяти пам'ять на 1 елемент кожен раз - погана ідея (якщо елементів буде більше ніж 300000+ то все буде відбуватися максимально повільно)
			// при тому що пам'ять вже виділена (є кепесіті), то доведеться зробити зсув для всіх існуючих елементів на 1 вправо
			for (int i = length - 1; i >= 0; i--) { // зсув іде справа наліво (тому що якщо робити його зліва направо, з початку масива в кінець) то можна втратити існуючі елементи
				data[i + 1] = data[i];
			}
			data[0] = value;
		}
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i + 1] = data[i];
			}
			// в новий масив в початок (по індексу 0) пишеться ОДИНАДЦЯТИЙ елемент
			temp[0] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void RemoveFromBack() {
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		int* temp = new int[length - 1];
		for (int i = 0; i < length - 1; i++) temp[i] = data[i];
		delete[] data;
		data = temp;
		length--;
	}

	void RemoveFromFront() {
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		int* temp = new int[length - 1];
		for (int i = 1; i < length; i++) data[i - 1] = data[i];
		delete[] data;
		data = temp;
		length--;
	}

	void Insert(int value, int index) {
		for (int i = length - 1; i >= 0; i--) {
			data[i + 1] = data[i];
		}
		data[index] = value;
		length++;
	}

	void RemoveByIndex(int index) {

		int* temp = new int[length - 1];
		for (int i = 0; i < index; i++) {
			temp[i] = data[i];
		}
		for (int i = index + 1; i < length; i++) {
			temp[i - 1] = data[i];
		}
		delete[] data;
		data = temp;
		length--;
	}

	void RemoveByValue(int value) {

		int* temp = new int[length - 1];
		for (int i = 0; i < length; i++) {
			if (data[i] == value)
			{
				int index = i;
				for (int j = 0; j < index; j++) {
					temp[j] = data[j];
				}
				for (int j = index + 1; j < length; j++) {
					temp[j - 1] = data[j];
				}
			}
		}
		delete[] data;
		data = temp;
		length--;
	}

	void Reverse() {
		for (int i = 0; i < length / 2; i++) {
			int bin = data[i];
			data[i] = data[length - 1 - i];
			data[length - 1 - i] = bin;
		}
	}

	void Sort()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length - i - 1; j++)
			{
				if (data[j] > data[j + 1]) {
					int bin = data[j];
					data[j] = data[j + 1];
					data[j + 1] = bin;
				}
			}
		}
	}

	void Shuffle() {
		for (int i = 0; i < length; i++) {
			int bin = data[i];
			data[i] = data[rand() % length];
			data[rand() % length] = bin;
		}
	}

	// написати:

	void Print() const {
		if (length == 0) {
			cout << "масив пустий!\n";
		}
		else {
			cout << "ємність масиву: " << capacity << "\n";
			cout << "елементи масиву: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i] << " ";
			}
			cout << "\n";
		}
	}

	~Vector() {
		cout << "D-TOR\n";
		if (data != nullptr) {
			delete[] data;
		}
	}

	Vector(const Vector& original) {
		cout << "COPY C-TOR\n";
		this->length = original.length;
		this->capacity = original.capacity;
		this->data = new int[capacity];
		for (int i = 0; i < length; i++)
			this->data[i] = original.data[i];
	}
};


int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	Vector a;

	for (int i = 0; i <= 1000; i++) {
		a.AddToFront(i);
		//a.Print();
	}
	 a.Print();

	 //a.RemoveFromBack();
	 //a.Print();

	 //a.Insert(21, 1);
	 //a.Print();

	 //a.RemoveByIndex(1);
	 //a.Print();

	 //a.Reverse();
	 //a.Print();

	 a.Sort();
	 a.Print();

	 //a.Shuffle();
	 //a.Print();

	 a.RemoveByValue(52);
	 a.Print();

	 //перевантаження операцій не зрозумів :(
}
