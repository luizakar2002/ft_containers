#include "utils.hpp"
#ifdef NAMESPACE
# include <vector>
# include <list>
# include <map>
# include <stack>
# include <queue>
# include <set>
#else
# define NAMESPACE ft
#endif

static bool
list_remove_666(int val)
{
	return (val != 666);
}

template <typename T>
static void
list_print_it(T& toto)
{
	typename T::iterator it;
	typename T::reverse_iterator itr;

	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << *it << " - " << *itr << std::endl;

	std::cout << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	if (toto.empty() == 0)
		std::cout << "  extrem() " << toto.front() << " >> " << toto.back() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void
main_list(void)
{
	NAMESPACE::list<int>	toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	std::cout << "---1" << std::endl;
	toto.push_back(1);
	toto.push_back(4);
	toto.push_back(2);
	toto.push_back(3);
	toto.push_back(5);
	toto.push_front(6);
	toto.push_back(7);
	list_print_it(toto);

	std::cout << "---2" << std::endl;
	toto.pop_front();
	toto.pop_back();
	list_print_it(toto);

	std::cout << "---3" << std::endl;
	NAMESPACE::list<int>::iterator it;
	it = toto.begin();
	for (int i = 0;i < 4;i++)
		it++;
	toto.insert(it, 8, 42);
	list_print_it(toto);

	std::cout << "---4" << std::endl;
	it = toto.erase(--it, toto.end());
	list_print_it(toto);

	std::cout << "---5" << std::endl;
	NAMESPACE::list<int>	tata(5, 42);
	toto.swap(tata);
	list_print_it(toto);
	list_print_it(tata);

	std::cout << "---6" << std::endl;
	toto.resize(10, 99);
	list_print_it(toto);

	std::cout << "---7" << std::endl;
	toto.resize(6);
	list_print_it(toto);

	std::cout << "---8" << std::endl;
	toto.clear();
	list_print_it(toto);

	std::cout << "---9" << std::endl;
	list_print_it(tata);
	tata.remove(1);
	tata.remove(42);
	list_print_it(tata);

	std::cout << "---10" << std::endl;
	tata.assign(5, 666);
	tata.remove_if(list_remove_666);
	list_print_it(tata);

	std::cout << "---11" << std::endl;
	tata.insert(tata.begin(), 4, 42);
	tata.insert(tata.end(), 3, 84);
	tata.push_back(666);
	tata.unique();
	list_print_it(tata);

	std::cout << "---12" << std::endl;
	tata.sort();
	tata.unique();
	list_print_it(tata);

	std::cout << "---13" << std::endl;
	toto.push_back(-214748368);
	toto.push_back(0);
	toto.push_back(50);
	toto.push_back(100);
	toto.push_back(8000);
	toto.push_back(2147483647);
	tata.merge(toto);
	list_print_it(tata);

	std::cout << "---14" << std::endl;
	tata.reverse();
	list_print_it(tata);

	std::cout << "---15" << std::endl;
	toto.push_front(8888);
	toto.push_front(8888);
	std::cout << "tata" << std::endl;
	list_print_it(tata);
	std::cout << "toto" << std::endl;
	list_print_it(toto);
	it = toto.begin();
	it++;
	std::cout << "toto == tata: " << (toto == tata) << " != " << (toto != tata) << std::endl;
	std::cout << "toto == toto: " << (toto == toto) << " != " << (toto != toto) << std::endl;
	std::cout << "tata == tata: " << (tata == tata) << " != " << (tata != tata) << std::endl;

	std::cout << "toto < tata: " << (toto < tata) << std::endl;
	std::cout << "toto > tata: " << (toto > toto) << std::endl;
	std::cout << "toto <= toto: " << (toto <= toto) << std::endl;
	std::cout << "toto >= toto: " << (toto >= toto) << std::endl;
}

template <typename T>
static void
vector_print_it(T& toto)
{
	typename T::iterator it;
	typename T::reverse_iterator itr;

	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << *it << " - " << *itr << std::endl;

	std::cout << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "capacity() " << toto.capacity() << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
//	if (toto.empty() == 0)
//		std::cout << "  extrem() " << toto.front() << " >> " << toto.back() << std::endl;
	std::cout << std::endl << std::endl;
}

void
main_vector(void)
{
	NAMESPACE::vector<int>	toto;

	std::cout << "max_size() " << toto.max_size() << std::endl;
	vector_print_it(toto);

	NAMESPACE::vector<int>	tata(10, 42);

	std::cout << "max_size() " << tata.max_size() << std::endl;
	vector_print_it(tata);

	tata.resize(5);
	vector_print_it(tata);

	tata.resize(8);
	vector_print_it(tata);

	tata.resize(11, 666);
	vector_print_it(tata);

	for (size_t i = 0;i < tata.size();i++)
		std::cout << i << " -> " << tata[i] << " | " << tata.at(i) << std::endl;
	try
	{
		tata.at(11);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "front: " << tata.front() << std::endl <<
					"back: " << tata.back() << std::endl << std::endl;

	toto.assign(5, 6);
	vector_print_it(toto);

	toto.assign(15, 60);
	vector_print_it(toto);

	toto.assign(tata.begin(), tata.end());
	vector_print_it(toto);

	toto.pop_back();
	toto.pop_back();
	toto.pop_back();
	toto.pop_back();
	toto.pop_back();
	vector_print_it(toto);

	for (int i = -42;i < -30;i++)
		toto.push_back(i);
	vector_print_it(toto);

	while (toto.size() > 0)
		toto.pop_back();
	for (int i = 0;i < 10;i++)
		toto.push_back(i);
	NAMESPACE::vector<int>::iterator it;
	it = toto.begin();
	it += 4;
	std::cout << "it: " << *it << std::endl;
	std::cout << "it: " << *(toto.insert(it, 80)) << std::endl;
	std::cout << "it: " << *(toto.insert(toto.end(), 80)) << std::endl;
	vector_print_it(toto);

	toto.insert(toto.end(), 10, 42);
	vector_print_it(toto);

	it = toto.begin();
	it += 5;
	toto.insert(it, 5, -666);
	vector_print_it(toto);

	it = toto.begin();
	it += 6;
	toto.insert(it, tata.begin(), tata.end());
	vector_print_it(toto);

	it = toto.begin();
	it += 2;
	std::cout << *(toto.erase(it)) << std::endl;
	vector_print_it(toto);

	std::cout << *(toto.erase(toto.end() - 1)) << std::endl;
	vector_print_it(toto);

	std::cout << *(toto.erase(toto.begin() + 10, toto.end() - 5)) << std::endl;
	vector_print_it(toto);

	std::cout << *(toto.erase(toto.end() - 6, toto.end() - 1)) << std::endl;
	vector_print_it(toto);

	toto.swap(tata);
	vector_print_it(toto);
	vector_print_it(tata);

	std::cout << "toto == tata: " << (toto == tata) << " != " << (toto != tata) << std::endl;
	std::cout << "toto == toto: " << (toto == toto) << " != " << (toto != toto) << std::endl;
	std::cout << "tata == tata: " << (tata == tata) << " != " << (tata != tata) << std::endl;

	std::cout << "toto < tata: " << (toto < tata) << std::endl;
	std::cout << "toto > tata: " << (toto > toto) << std::endl;
	std::cout << "toto <= toto: " << (toto <= toto) << std::endl;
	std::cout << "toto >= toto: " << (toto >= toto) << std::endl;

	toto.clear();
	tata.clear();
	vector_print_it(toto);
	vector_print_it(tata);
}

template <typename T>
static void
map_print_it(T& toto)
{
	typename T::iterator it;
	typename T::reverse_iterator itr;

	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << it->first << "|" << it->second << " - " << itr->first << "|" << itr->second << std::endl;

	std::cout << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

template <typename T>
static void
map_print_op(T& toto)
{
	std::cout << " http: " << toto["http"] << std::endl;
	std::cout << "https: " << toto["https"] << std::endl;
	std::cout << "  ssh: " << toto["ssh"] << std::endl;
	std::cout << "ecole: " << toto["ecole"] << std::endl;
	std::cout << std::endl << std::endl;
}

void
main_map(void)
{
	NAMESPACE::map<std::string, int>	toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	std::cout << "---1" << std::endl;
	toto.insert(NAMESPACE::pair<std::string, int>("ecole", 42));
	toto.insert(NAMESPACE::pair<std::string, int>("truc", 1));
	toto.insert(NAMESPACE::pair<std::string, int>("trac", 66));
	toto.insert(NAMESPACE::pair<std::string, int>("hexa", 666));
	toto.insert(NAMESPACE::pair<std::string, int>("ssh", 22));
	toto.insert(NAMESPACE::pair<std::string, int>("http", 80));
	toto.insert(NAMESPACE::pair<std::string, int>("https", 443));
	map_print_it(toto);

	std::cout << "---2" << std::endl;
	toto.erase("ecole");
	map_print_op(toto);

	std::cout << "---3" << std::endl;
	NAMESPACE::map<std::string, int>	tata(toto);
	map_print_it(tata);

	std::cout << "---4" << std::endl;
	tata.clear();
	map_print_it(tata);
	map_print_it(toto);

	std::cout << "---5" << std::endl;
	tata.swap(toto);
	map_print_it(tata);
	map_print_it(toto);

	std::cout << "---6" << std::endl;
	toto.insert(tata.begin(), tata.end());
	map_print_it(tata);
}

template <typename T>
void
stack_print_info(T& toto)
{
	std::cout << "empty(): " << toto.empty() << std::endl;
	std::cout << " size(): " << toto.size() << std::endl;
	if (toto.size() > 0)
		std::cout << "  top(): " << toto.top() << std::endl;
	std::cout << std::endl << std::endl;
}

void
main_stack(void)
{
	NAMESPACE::stack<int>	toto;

	std::cout << "---1" << std::endl;
	stack_print_info(toto);

	std::cout << "---2" << std::endl;
	for(size_t i = 0;i < 42;i++)
		toto.push(i);
	stack_print_info(toto);

	std::cout << "---3" << std::endl;
	for(size_t i = 0;i < 21;i++)
		toto.pop();
	stack_print_info(toto);
}

template <typename T>
void
queue_print_info(T& toto)
{
	std::cout << "empty(): " << toto.empty() << std::endl;
	std::cout << " size(): " << toto.size() << std::endl;
	if (toto.size() > 0)
	{
		std::cout << " back(): " << toto.back() << std::endl;
		std::cout << "front(): " << toto.front() << std::endl;
	}
	std::cout << std::endl << std::endl;
}

void
main_queue(void)
{
	NAMESPACE::queue<int>	toto;

	std::cout << "---1" << std::endl;
	queue_print_info(toto);

	std::cout << "---2" << std::endl;
	for(size_t i = 0;i < 42;i++)
		toto.push(i);
	queue_print_info(toto);

	std::cout << "---3" << std::endl;
	for(size_t i = 0;i < 21;i++)
		toto.pop();
	queue_print_info(toto);
}

template <typename T>
static void
set_print_it(T& toto)
{
	typename T::iterator it;
	typename T::reverse_iterator itr;

	it = toto.begin();
	itr = toto.rbegin();
	for (;it != toto.end();it++, itr++)
		std::cout << "  iterator " << *it << " - " << *itr << std::endl;

	std::cout << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << std::endl << std::endl;
}

void
main_set(void)
{
	NAMESPACE::set<std::string>		toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	std::cout << "---1" << std::endl;
	toto.insert("ecole");
	toto.insert("truc");
	toto.insert("trac");
	toto.insert("hexa");
	toto.insert("ssh");
	toto.insert("http");
	toto.insert("https");
	set_print_it(toto);

	std::cout << "---2" << std::endl;
	toto.erase("ecole");
	set_print_it(toto);

	std::cout << "---3" << std::endl;
	NAMESPACE::set<std::string>		tata(toto);
	set_print_it(tata);

	std::cout << "---4" << std::endl;
	tata.clear();
	set_print_it(tata);
	set_print_it(toto);

	std::cout << "---5" << std::endl;
	tata.swap(toto);
	set_print_it(tata);
	set_print_it(toto);

	std::cout << "---6" << std::endl;
	toto.insert(tata.begin(), tata.end());
	set_print_it(tata);
}

void
main_multiset(void)
{
	NAMESPACE::multiset<std::string>	toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	std::cout << "---1" << std::endl;
	toto.insert("ecole");
	toto.insert("ecole");
	toto.insert("ecole");
	toto.insert("ecole");
	toto.insert("truc");
	toto.insert("trac");
	toto.insert("hexa");
	toto.insert("ssh");
	toto.insert("http");
	toto.insert("https");
	set_print_it(toto);

	std::cout << "---2" << std::endl;
	toto.erase("ecole");
	set_print_it(toto);

	std::cout << "---3" << std::endl;
	NAMESPACE::multiset<std::string>	tata(toto);
	set_print_it(tata);

	std::cout << "---4" << std::endl;
	tata.clear();
	set_print_it(tata);
	set_print_it(toto);

	std::cout << "---5" << std::endl;
	tata.swap(toto);
	set_print_it(tata);
	set_print_it(toto);

	std::cout << "---6" << std::endl;
	toto.insert(tata.begin(), tata.end());
	set_print_it(tata);
}

void
main_multimap(void)
{
	NAMESPACE::multimap<std::string, int>	toto;

	std::cout << "   empty() " << toto.empty() << std::endl;
	std::cout << "    size() " << toto.size() << std::endl;
	std::cout << "max_size() " << toto.max_size() << std::endl;
	
	std::cout << "---1" << std::endl;
	toto.insert(NAMESPACE::pair<std::string, int>("ecole", 42));
	toto.insert(NAMESPACE::pair<std::string, int>("truc", 1));
	toto.insert(NAMESPACE::pair<std::string, int>("trac", 66));
	toto.insert(NAMESPACE::pair<std::string, int>("hexa", 666));
	toto.insert(NAMESPACE::pair<std::string, int>("ssh", 22));
	toto.insert(NAMESPACE::pair<std::string, int>("http", 80));
	toto.insert(NAMESPACE::pair<std::string, int>("https", 443));
	map_print_it(toto);

	std::cout << "---2" << std::endl;
	toto.erase("ecole");
	map_print_it(toto);

	std::cout << "---3" << std::endl;
	NAMESPACE::multimap<std::string, int>	tata(toto);
	tata.insert(toto.rbegin(), toto.rend());
	map_print_it(tata);

	std::cout << "---4" << std::endl;
	tata.clear();
	map_print_it(tata);
	map_print_it(toto);

	std::cout << "---5" << std::endl;
	tata.swap(toto);
	map_print_it(tata);
	map_print_it(toto);

	std::cout << "---6" << std::endl;
	toto.insert(tata.begin(), tata.end());
	map_print_it(tata);
}

int
main(void)
{
	std::cout << "===== LIST =====" << std::endl;
	main_list();
	std::cout << std::endl;

	std::cout << "===== VECTOR =====" << std::endl;
	main_vector();
	std::cout << std::endl;

	std::cout << "===== MAP =====" << std::endl;
	main_map();
	std::cout << std::endl;

	std::cout << "===== STACK =====" << std::endl;
	main_stack();
	std::cout << std::endl;

	std::cout << "===== QUEUE =====" << std::endl;
	main_queue();
	std::cout << std::endl;

	std::cout << "===== SET =====" << std::endl;
	main_set();
	std::cout << std::endl;

	std::cout << "===== MULTISET =====" << std::endl;
	main_multiset();
	std::cout << std::endl;

	std::cout << "===== MULTIMAP =====" << std::endl;
	main_multimap();
	std::cout << std::endl;
}
