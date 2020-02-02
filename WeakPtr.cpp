#include "pch.h"
#include <iostream>

/*
Реализовать аналог weak_ptr :
1. Инициализацию через конструктор;
2. Оператор присваивания;
3. Аналог reset();
4. Получения значения счетчика ссылок;
5. Аналог expired() - проверка удалён ли объект на который ссылается weak_ptr;
6. Аналог lock() - создает shared_ptr, который управляет объектом, на который ссылается weak_ptr.
*/

int main()
{
	std::shared_ptr<int> sp(new int);

	WeakPtr<int> wp1;
	WeakPtr<int> wp2(wp1);
	WeakPtr<int> wp3(sp);

	std::cout << "use_count:\n";
	std::cout << "wp1: " << wp1.GetUseCount() << '\n';
	std::cout << "wp2: " << wp2.GetUseCount() << '\n';
	std::cout << "wp3: " << wp3.GetUseCount() << '\n';

	std::cout << "sp: " << sp.use_count() << '\n';



	
	std::shared_ptr<int> sp1, sp2;
	WeakPtr<int> wp4;
	
	sp1 = std::make_shared<int>(10);    // sp1
	wp4 = sp1;                            // sp1, wp

	sp2 = wp4.Lock();                     // sp1, wp, sp2
	sp1.reset();                         //      wp, sp2

	sp1 = wp4.Lock();                     // sp1, wp, sp2

	std::cout << "*sp1: " << *sp1 << '\n';
	std::cout << "*sp2: " << *sp2 << '\n';

	

	std::shared_ptr<int> sp3(new int(10));

	WeakPtr<int> wp5(sp3);

	std::cout << "1. wp " << (wp5.Expired() ? "is" : "is not") << " expired\n";

	wp5.Reset();

	std::cout << "2. wp " << (wp5.Expired() ? "is" : "is not") << " expired\n";
}

