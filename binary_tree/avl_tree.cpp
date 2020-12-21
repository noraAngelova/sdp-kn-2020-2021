#ifndef AVL_TREE
#define AVL_TREE

#include "binary_search_tree.cpp"
#include <iostream>

// Елемент в AVL дърво
// Трябва да съдържа стойността на върха и баланс фактор
template <typename T>
class AVLElement {
private:
	T data;
	int balance;
public:
	AVLElement(T const& _data = T(), int _balance = 0)
		: data(_data), balance(_balance) {}

	// Ивличане на стойността по референция
	T& getData() {
		return data;
	}

	// Ивличане на баланс фактор по референция
	int& getBalance() {
		return balance;
	}

	// Оператори за сравнение на елементи
	// Сравняват се само стойностите и balance се игнорира
	bool operator<(AVLElement const& elem) const {
		return data < elem.data;
	}

	bool operator==(AVLElement const& elem) const {
		return data == elem.data;
	}

	// Предефинират се останалите методи чрез първите два
	// Може да се използва сравнение с data
	bool operator!=(AVLElement const& elem) const {
		return !(*this == elem);
	}

	bool operator>=(AVLElement const& elem) const {
		return !(*this < elem);
	}

	bool operator<=(AVLElement const& elem) const {
		return *this < elem || *this == elem;
	}

	bool operator>(AVLElement const& elem) const {
		return !(*this <= elem);
	}
};

// Извеждане на елемент на AVL дърво
// Функцията е външна за класа
template <typename T>
std::ostream& operator<<(std::ostream& os, AVLElement<T> elem) {
	return os << elem.getData();
}

// AVL дърво
template <typename T>
class AVLTree : protected BSTree<AVLElement<T>> {
private:
	void rotateLeft(BinTreePosition<AVLElement<T>> x) {
		BinTree<AVLElement<T>> tmp;
		BinTreePosition<AVLElement<T>> y = tmp.rootPos();
		BinTree<AVLElement<T>>::assignFrom(y, +x);
		
		int& bx = (*x).getBalance();
		int& by = (*y).getBalance();

		std::cout << bx << " " << by;

		BinTree<AVLElement<T>>::assignFrom(+x, -y);
		BinTree<AVLElement<T>>::assignFrom(-y, x);
		BinTree<AVLElement<T>>::assignFrom(x, y);

		// Височината на дясното поддърво е намалена с 1
		// Баланс факторът на дървото се намалява най-малко с 1
		if (by <= 0)
			bx--;
		else
			bx -= by + 1;

		if (bx >= 0)
			by--;
		else
			by += bx - 1;	

	}

	void rotateRight(BinTreePosition<AVLElement<T>> y) {
		BinTree<AVLElement<T>> tmp;
		BinTreePosition<AVLElement<T>> x = tmp.rootPos();
		BinTree<AVLElement<T>>::assignFrom(x, -y);
		std::cout << "right2";

		int& bx = (*x).getBalance();
		int& by = (*y).getBalance();

		BinTree<AVLElement<T>>::assignFrom(-y, +x);
		BinTree<AVLElement<T>>::assignFrom(+x, y);
		BinTree<AVLElement<T>>::assignFrom(y, x);

		if (bx >= 0)
			by++;
		else
			by -= bx - 1;

		if (by <= 0)
			bx++;
		else
			bx += by + 1;
	}

	// Добавя елемент и връща информация дали е добавен и дали е променана височината на дървото
	// -1 - неуспешно включване, елементът вече го има
	//  0 - успешно включване, няма промяна във височината
	//  1 - успешно включване, има увеличение на височината с 1
	int insertAt(BinTreePosition<AVLElement<T>> p, T const& x) {
		// Стигнали сме до невалидна позиция в дървото
		if (!p) {
			// Създава се дърво с единствен връх - корена на дървото
			BinTree<AVLElement<T>> tree = AVLElement<T>(x);
			// Взима се паметта за този връх в дървото
			BinTree<AVLElement<T>>::assignFrom(p, tree.rootPos());
			return 1;
		}

		// Текущата позиция е валидна позиция в дървото
		
		
		// Проверяваме дали стойността съвпада с тази, която трябва да бъде добавена
		if ((*p).getData() == x) {
			// Елементът не може да бъде добавен повторно
			return -1;
		}

		// Намираме се на валидна позиция и стойността е различна от х
		int result;
		if (x < (*p).getData()) {
			// Елементът трябва да се добави в лявото поддърво
			result = insertAt(-p, x);

			// Добавянето може да е било неуспешно и тогава трябва само да върнем резултата
			// Добавяне може да е било успешно и да не е проминело височината на дървото, балансираността е запазена
			// Дабабявето може да е било успешно и да има промяна във височината на дървото -> да се провери балансираността
			if (result == 1) {
				// Балансът на текущият възел се намалява с 1, височината на лявото поддърво е с 1-ца по-голяма
				(*p).getBalance()--;

				// Проверява се новата стойност и дали балансираността е нарушена
				if ((*p).getBalance() == -2) {
					// Нужна ли е лява ротация
					if ((*-p).getBalance() == 1) {
						rotateLeft(-p);
					}
					rotateRight(p);
					
					// Балансираността и височината е възстановена
					// Не са нужни промени нагоре по дървото
					result = 0;
				}
			}
		}
		else {
			// Елементът трябва да се добави в лявото поддърво
			result = insertAt(+p, x);
			
			// Добавянето може да е било неуспешно и тогава трябва само да върнем резултата
			// Добавяне може да е било успешно и да не е проминело височината на дървото, балансираността е запазена
			// Дабабявето може да е било успешно и да има промяна във височината на дървото -> да се провери балансираността
			if (result == 1) {
				// Балансът на текущият възел се увеличава с 1, височината на дясното поддърво е с 1-ца по-голяма
				(*p).getBalance()++;

				// Проверява се новата стойност и дали балансираността е нарушена
				if ((*p).getBalance() == 2) {
					// Нужна ли е дясна ротация
					if ((*+p).getBalance() == -1) {
						rotateRight(+p);
					}
					rotateLeft(p);

					// Балансираността и височината е възстовена
					// Не са нужни промени нагоре по дървото
					result = 0;
				}
			}
		}
		// Ако операцията е успешна и балансът се е получил 0, няма промяна във височината
		if (result >= 0 && (*p).getBalance() == 0) {
			result = 0;
		}
		
		return result;
	}

public:
	// Търсене на елемент в AVL дърво
	BinTreePosition<AVLElement<T>> search(T const& x) {
		return BSTree<AVLElement<T>>::search(x);
	}

	// Вмъква елемент в AVL дърво
	// Добавянето е успешно, независимо от това дали има промяна на височината
	bool insert(T const& x) {
		return insertAt(BSTree<AVLElement<T>>::rootPos(), x) >= 0;
	}

  // Добавяме метод за извеждане на елементи
	void print(std::ostream& out) {
		BSTree<AVLElement<T>>::print(out);
	}
};

#endif

