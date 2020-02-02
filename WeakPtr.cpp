#include "pch.h"
#include <iostream>

/*
����������� ������ weak_ptr :
1. ������������� ����� �����������;
2. �������� ������������;
3. ������ reset();
4. ��������� �������� �������� ������;
5. ������ expired() - �������� ����� �� ������ �� ������� ��������� weak_ptr;
6. ������ lock() - ������� shared_ptr, ������� ��������� ��������, �� ������� ��������� weak_ptr.
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

