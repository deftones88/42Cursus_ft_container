#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <stack>
#include "iterator.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"


#define TITLE "\e[37;41m"
#define SUBTITLE "\e[30;46m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define MINE "\e[1;33m" // pink
#define COMP "\e[1;34m" // blue
#define MAGENTA "\e[1;35m"
#define ENDCOLOR "\e[0m"

using std::cout;
using std::endl;
using std::setw;
using std::string;

int main() {
	cout<< TITLE<< setw(30)<<std::right<<" << VECTOR >> "<<setw(20)<<ENDCOLOR<<endl;
	ft::vector<int> ftv_int;
	std::vector<int> stdv_int;
	cout << SUBTITLE <<setw(30)<<std::right<< " -- s i z e -- "<<setw(20)<<ENDCOLOR<<endl;
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : \t"<<ftv_int.size()<<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : \t"<<stdv_int.size()<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "-- max_size --"<<setw(20)<<ENDCOLOR<<endl;
	cout << MINE << setw(20)<<std::left
		<<"ftv_int"<<" : \t"<<ftv_int.max_size()<<setw(7)<<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left
		<<"stdv_int"<<" : \t"<<stdv_int.max_size()<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "-- push_back --"<<setw(20)<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "     0 ~ 5     "<<setw(20)<<ENDCOLOR<<endl;
	for (size_t i = 0; i < 5; i++) {
		ftv_int.push_back(i);
		stdv_int.push_back(i);
	}
	ft::vector<int>::iterator ftv_it;
	std::vector<int>::iterator stdv_it;
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : \t";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it) cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : \t";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it) cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< " -- assign -- "<<setw(20)<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "    2, 42     "<<setw(20)<<ENDCOLOR<<endl;
	ftv_int.assign(2, 42);
	stdv_int.assign(2, 42);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : \t";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : \t";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< " -- insert -- "<<setw(20)<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "      50      "<<setw(20)<<ENDCOLOR<<endl;
	ftv_it = ftv_int.insert(ftv_int.begin(), 50);
	stdv_it = stdv_int.insert(stdv_int.begin(), 50);
	cout << MINE << setw(20)<<std::left<<"return value"<<" : \t"<<*ftv_it<<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"return value"<<" : \t"<<*stdv_it<<ENDCOLOR<<endl;
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : \t";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : \t";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "     3 10     "<<setw(20)<<ENDCOLOR<<endl;
	ftv_int.insert(ftv_int.begin() + 2, 3, 10);
	stdv_int.insert(stdv_int.begin() + 2, 3, 10);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(30)<<std::right<< "end 1 3    "<<setw(20)<<ENDCOLOR<<endl;
	ftv_int.insert(ftv_int.end(), ftv_int.begin(), ftv_int.begin() + 3);
	stdv_int.insert(stdv_int.end(), stdv_int.begin(), stdv_int.begin() + 3);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(28)<<std::right<< " -- resize --"<<setw(22)<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(28)<<std::right<< " resize to 5"<<setw(22)<<ENDCOLOR<<endl;
	ftv_int.resize(5);
	stdv_int.resize(5);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(28)<<std::right<< " resize to 7"<<setw(22)<<ENDCOLOR<<endl;
	ftv_int.resize(7);
	stdv_int.resize(7);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(32)<<std::right<< "resize to 10 with 4"<<setw(18)<<ENDCOLOR<<endl;
	ftv_int.resize(10, 4);
	stdv_int.resize(10, 4);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(28)<<std::right<< " -- swap --"<<setw(22)<<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(28)<<std::right<< " before  "<<setw(22)<<ENDCOLOR<<endl;
	ft::vector<int> ftv_swap;
	std::vector<int> stdv_swap;
	for (size_t i = 1; i < 6; i++) {
		ftv_swap.push_back(i);
		stdv_swap.push_back(i);
	}
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << MINE << setw(20)<<std::left<<"ftv_swap"<<" : ";
	for (ftv_it = ftv_swap.begin(); ftv_it != ftv_swap.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_swap"<<" : ";
	for (stdv_it = stdv_swap.begin(); stdv_it != stdv_swap.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(28)<<std::right<< " after  "<<setw(22)<<ENDCOLOR<<endl;
	ftv_int.swap(ftv_swap);
	stdv_int.swap(stdv_swap);
	cout << MINE << setw(20)<<std::left<<"ftv_int"<<" : ";
	for (ftv_it = ftv_int.begin(); ftv_it != ftv_int.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << MINE << setw(20)<<std::left<<"ftv_swap"<<" : ";
	for (ftv_it = ftv_swap.begin(); ftv_it != ftv_swap.end(); ++ftv_it)
		cout<< *ftv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_int"<<" : ";
	for (stdv_it = stdv_int.begin(); stdv_it != stdv_int.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"stdv_swap"<<" : ";
	for (stdv_it = stdv_swap.begin(); stdv_it != stdv_swap.end(); ++stdv_it)
		cout<< *stdv_it<<" ";
	cout <<ENDCOLOR<<endl;

	cout << SUBTITLE <<setw(33)<<std::right<< " -- const_iterator --"<<setw(17)<<ENDCOLOR<<endl;
	ftv_it = ftv_int.begin();
	stdv_it = stdv_int.begin();
	ft::vector<int>::const_iterator ftv_cit = ftv_it;
	std::vector<int>::const_iterator stdv_cit = stdv_it;
	cout << MINE << setw(20)<<std::left<<"const ftv"<<" : ";
	for (; ftv_cit != ftv_int.end(); ++ftv_cit)
		cout<< *ftv_cit<<" ";
	cout <<ENDCOLOR<<endl;
	cout << COMP << setw(20)<<std::left<<"const stdv"<<" : ";
	for (; stdv_cit != stdv_int.end(); ++stdv_cit)
		cout<< *stdv_cit<<" ";
	cout <<ENDCOLOR<<endl;
	cout << SUBTITLE <<setw(33)<<std::right<< " -- operator[] --"<<setw(17)<<ENDCOLOR<<endl;
	for (size_t i = 0; i < ftv_int.size(); i++)
		cout << MINE << "ftv_int["<<i<<"]  = "<< ftv_int[i]<<", ";
	cout <<ENDCOLOR<<endl;
	for (size_t i = 0; i < stdv_int.size(); i++)
		cout << COMP << "stdv_int["<<i<<"] = "<< stdv_int[i]<<", ";
	cout <<ENDCOLOR<<endl;

	cout<< TITLE<< setw(28)<<std::right<<" << M A P >> "<<setw(22)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<"  -- insert --"<<setw(22)<<ENDCOLOR<<endl;
	ft::map<int, int> ftm;
	std::map<int, int> stdm;
	cout<< SUBTITLE<< setw(28)<<std::right<<" value   "<<setw(22)<<ENDCOLOR<<endl;
	ft::pair<ft::map<int,int>::iterator, bool> pr = ftm.insert(ft::pair<int, int>(1, 2));
	ft::map<int,int>::iterator it = pr.first;
	bool b = pr.second;
	cout<< MINE<<"- pair : (1,2)\t\t- ft_map  : ("<<(*it).first<<", "<<(*it).second;
	if (b) cout<<") [YES]"<<ENDCOLOR<<endl;
	else   cout<<") [NO]"<<ENDCOLOR<<endl;
	std::pair<std::map<int,int>::iterator, bool> stdpr = stdm.insert(std::pair<int, int>(1, 2));
	std::map<int,int>::iterator stdit = stdpr.first;
	bool b2 = stdpr.second;
	cout<< COMP<<"- pair : (1,2)\t\t- std_map : ("<<(*stdit).first<<", "<<(*stdit).second;
	if (b2) cout<<") [YES]"<<ENDCOLOR<<endl;
	else   cout<<") [NO]"<<ENDCOLOR<<endl;
	ftm.print();
	pr = ftm.insert(ft::pair<int, int>(3, 4));
	it = pr.first;
	b = pr.second;
	cout<< MINE<<"- pair : (3,4)\t\t- ft_map  : ("<<(*it).first<<", "<<(*it).second;
	if (b) cout<<") [YES]"<<ENDCOLOR<<endl;
	else   cout<<") [NO]"<<ENDCOLOR<<endl;
	stdpr = stdm.insert(std::pair<int, int>(3, 4));
	stdit = stdpr.first;
	b2 = stdpr.second;
	cout<< COMP<<"- pair : (3,4)\t\t- std_map : ("<<(*stdit).first<<", "<<(*stdit).second;
	if (b2) cout<<") [YES]"<<ENDCOLOR<<endl;
	else   cout<<") [NO]"<<ENDCOLOR<<endl;
	ftm.print();
	pr = ftm.insert(ft::pair<int, int>(1, 4));
	it = pr.first;
	b = pr.second;
	cout<< MINE<<"- pair : (1,4)\t\t- ft_map  : ("<<(*it).first<<", "<<(*it).second;
	if (b) cout<<") [YES]"<<endl;
	else   cout<<") [NO]"<<endl;
	stdpr = stdm.insert(std::pair<int, int>(1, 4));
	stdit = stdpr.first;
	b2 = stdpr.second;
	cout<< COMP<<"- pair : (1,4)\t\t- std_map : ("<<(*stdit).first<<", "<<(*stdit).second;
	if (b2) cout<<") [YES]"<<ENDCOLOR<<endl;
	else   cout<<") [NO]"<<ENDCOLOR<<endl;
	ftm.print();
	cout<<endl;

	cout<< SUBTITLE<< setw(30)<<std::right<<" iterator, value"<<setw(20)<<ENDCOLOR<<endl;
	it = ftm.insert(ftm.end(), ft::pair<int, int>(2, 5));
	cout<< "- pair : (2,5)"<<endl;
	stdit = stdm.insert(stdm.end(), std::pair<int, int>(2, 5));
	ftm.print();
	cout<<"- pair : (2,5)"<<endl;
	it = ftm.insert(ftm.end(), ft::pair<int, int>(2, 5));
	stdit = stdm.insert(stdm.end(), std::pair<int, int>(2, 5));
	ftm.print();
	cout<< "- pair : (4,5)"<<endl;
	it = ftm.insert(ftm.end(), ft::pair<int, int>(4, 5));
	stdit = stdm.insert(stdm.end(), std::pair<int, int>(4, 5));
	ftm.print();
	cout<<endl;

	cout<< SUBTITLE<< setw(31)<<std::right<<"iterator, iterator"<<setw(19)<<ENDCOLOR<<endl;
	cout<<"- { (6,7), (7,7), (8,5) } -> begin, end"<<endl;
	ft::vector<ft::pair<int, int> > v;
	v.push_back(ft::pair<int, int>(6,7));
	v.push_back(ft::pair<int, int>(7,7));
	v.push_back(ft::pair<int, int>(8,5));
	ftm.insert(v.begin(), v.end());
	std::vector<std::pair<int, int> > stdv;
	stdv.push_back(std::pair<int, int>(6,7));
	stdv.push_back(std::pair<int, int>(7,7));
	stdv.push_back(std::pair<int, int>(8,5));
	stdm.insert(stdv.begin(), stdv.end());
	ftm.print();


	cout<< SUBTITLE<< setw(28)<<std::right<<"  -- count --"<<setw(22)<<ENDCOLOR<<endl;
	for (size_t i = 0; i < 10; i++)
		cout<<"count of "<<i<<"  :\t"<<MINE<<ftm.count(i)<<"\t"<<COMP<<stdm.count(i)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<"  -- key_comp --"<<setw(22)<<ENDCOLOR<<endl;
	ft::map<int, int>::key_compare _comp = ftm.key_comp();
	int highest = ftm.rbegin()->first;
	for (it = ftm.begin(); it != ftm.end(); ++it) {
		cout <<MINE<< (*it).first <<" is ";
		if (!_comp((*it).first, highest)) cout<<"not ";
			cout<<"smaller than "<<highest << ENDCOLOR<<endl;
	}
	highest = stdm.rbegin()->first;
	for (stdit = stdm.begin(); stdit != stdm.end(); ++stdit) {
		cout <<COMP<<"\t\t\t"<< (*stdit).first <<" is ";
		if (!_comp((*stdit).first, highest)) cout<<"not ";
			cout<<"smaller than "<<highest << ENDCOLOR<<endl;
	}

	cout<< SUBTITLE<< setw(38)<<std::right<<"-lower_bound & upper_bound-"<<setw(12)<<ENDCOLOR<<endl;
	for (size_t i = 0; i < 8; i++) {
		it = ftm.lower_bound(i);
		cout << MINE<<i<<": lower_bound "<<it->first;
		it = ftm.upper_bound(i);
		cout<<", upper_bound "<<it->first<<ENDCOLOR<<endl;
		stdit = stdm.lower_bound(i);
		cout << COMP<<i<<": lower_bound "<<stdit->first;
		stdit = stdm.upper_bound(i);
		cout<<", upper_bound "<<stdit->first<<ENDCOLOR<<endl;
	}
	cout<< SUBTITLE<< setw(28)<<std::right<<"-- equal_range --"<<setw(22)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<" 6       "<<setw(22)<<ENDCOLOR<<endl;
	ft::pair<ft::map<int,int>::iterator, ft::map<int,int>::iterator> eq = ftm.equal_range(6);
	cout <<MINE<< "lower_bound : ("<<eq.first->first<<", "<<eq.first->second<<")\t";
	cout << "upper_bound : ("<<eq.second->first<<", "<<eq.second->second<<")"<<ENDCOLOR<<endl;
	std::pair<std::map<int,int>::iterator, std::map<int,int>::iterator> stdeq = stdm.equal_range(6);
	cout <<COMP<< "lower_bound : ("<<stdeq.first->first<<", "<<stdeq.first->second<<")\t";
	cout << "upper_bound : ("<<stdeq.second->first<<", "<<stdeq.second->second<<")"<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<"-- operator[] --"<<setw(22)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<" map[5] = 10 "<<setw(22)<<ENDCOLOR<<endl;
	ftm[5] = 10;
	stdm[5] = 10;
	ftm.print();
	cout<< SUBTITLE<< setw(28)<<std::right<<" map[6] = 6 "<<setw(22)<<ENDCOLOR<<endl;
	it = ftm.lower_bound(6);
	cout <<MINE<< "original : ("<<it->first<<", "<<it->second;
	ftm[6] = 6;
	cout << ")\tafter : ("<<it->first<<", "<<it->second<<")"<<ENDCOLOR<<endl;
	stdit = stdm.lower_bound(6);
	cout <<COMP<< "original : ("<<stdit->first<<", "<<stdit->second;
	stdm[6] = 6;
	cout << ")\tafter : ("<<stdit->first<<", "<<stdit->second<<")"<<ENDCOLOR<<endl;
	for (it = ftm.begin(); it != ftm.end(); ++it)
		cout<<MINE<<"ftm ["<<it->first<<"] = "<<ftm[it->first]<<", ";
	cout<<ENDCOLOR<<endl;
	for (stdit = stdm.begin(); stdit != stdm.end(); ++stdit)
		cout<<COMP<<"stdm["<<stdit->first<<"] = "<<stdm[stdit->first]<<", ";
	cout<<ENDCOLOR<<endl;

	cout<< SUBTITLE<< setw(28)<<std::right<<"-- erase --"<<setw(22)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<" value : 6"<<setw(22)<<ENDCOLOR<<endl;
	cout << MINE<<"item erased : "<<ftm.erase(6) << endl;
	for (it = ftm.begin(); it != ftm.end(); ++it)
		cout<<MINE<<"ftm ["<<it->first<<"] = "<<ftm[it->first]<<ENDCOLOR<<", ";
	cout<<ENDCOLOR<<endl;
	cout << COMP<<"item erased : "<<stdm.erase(6) << endl;
	for (stdit =stdm.begin(); stdit != stdm.end(); ++stdit)
		cout<<COMP<<"stdm["<<stdit->first<<"] = "<<stdm[stdit->first]<<", ";
	cout<<ENDCOLOR<<endl;
	ftm.print();
	cout<< SUBTITLE<< setw(28)<<std::right<<"iterator : begin"<<setw(22)<<ENDCOLOR<<endl;
	ftm.erase(ftm.begin());
	for (it = ftm.begin(); it != ftm.end(); ++it)
		cout<<MINE<<"ftm ["<<it->first<<"] = "<<ftm[it->first]<<ENDCOLOR<<", ";
	cout<<ENDCOLOR<<endl;
	stdm.erase(stdm.begin());
	for (stdit = stdm.begin(); stdit != stdm.end(); ++stdit)
		cout<<COMP<<"stdm["<<stdit->first<<"] = "<<stdm[stdit->first]<<ENDCOLOR<<", ";
	cout<<ENDCOLOR<<endl;
	ftm.print();
	cout<< SUBTITLE<< setw(33)<<std::right<<"iterator, iterator : 4~7"<<setw(17)<<ENDCOLOR<<endl;
	ftm.erase(ftm.find(4), --ftm.end());
	for (it = ftm.begin(); it != ftm.end(); ++it)
		cout<<MINE<<"ftm ["<<it->first<<"] = "<<ftm[it->first]<<ENDCOLOR<<", ";
	cout<<ENDCOLOR<<endl;
	stdm.erase(stdm.find(4), --stdm.end());
	for (stdit = stdm.begin(); stdit != stdm.end(); ++stdit)
		cout<<COMP<<"stdm["<<stdit->first<<"] = "<<stdm[stdit->first]<<ENDCOLOR<<", ";
	cout<<ENDCOLOR<<endl;
	ftm.print();
	cout<< SUBTITLE<< setw(28)<<std::right<<"-- clear --"<<setw(22)<<ENDCOLOR<<endl;
	ftm.clear();
	stdm.clear();
	ftm.print();

	cout<< TITLE<< setw(28)<<std::right<<" << STACK >>"<<setw(22)<<ENDCOLOR<<endl;
	ft::stack<int> mystack;
	std::stack<int> stdstack;
	cout<< SUBTITLE<< setw(28)<<std::right<<"-- push --  "<<setw(22)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<" 0 ~ 9    "<<setw(22)<<ENDCOLOR<<endl;
	for (int i = 0; i < 10; i++)  {
		mystack.push(i);
		stdstack.push(i);
	}
	cout << "- size :\t"<<MINE << mystack.size() << "\t"<<COMP<<stdstack.size()<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<"-- pop --   "<<setw(22)<<ENDCOLOR<<endl;
	mystack.pop();
	stdstack.pop();
	cout << "- size :\t" << MINE<<mystack.size()<<"\t"<<COMP<<stdstack.size() << ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(30)<<std::right<<"-- empty & top --"<<setw(20)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(28)<<std::right<<"top += 5  "<<setw(22)<<ENDCOLOR<<endl;
	cout<< SUBTITLE<< setw(33)<<std::right<<"relational operators"<<setw(17)<<ENDCOLOR<<endl;
	while (!mystack.empty()) {
		cout<<MINE<< "top ( " <<mystack.top()<<" )   += 5";
		mystack.top() += 5;
		cout<< "   ->   "<<mystack.top() <<"\t ";
		if (mystack.top() == 9) 		cout<< " [ = ] ";
		else if (mystack.top() > 9)		cout<< " [ > ] ";
		else if (mystack.top() < 9)		cout<< " [ < ] ";
		mystack.pop();
		cout<<"9"<<ENDCOLOR<<endl;
	}
	while (!stdstack.empty()) {
		cout<<COMP<< "top ( " <<stdstack.top()<<" )   += 5";
		stdstack.top() += 5;
		cout<< "   ->   "<<stdstack.top() <<"\t ";
		if (stdstack.top() == 9) 		cout<< " [ = ] ";
		else if (stdstack.top() > 9)	cout<< " [ > ] ";
		else if (stdstack.top() < 9)	cout<< " [ < ] ";
		stdstack.pop();
		cout<<"9"<<ENDCOLOR<<endl;
	}
	return 0;
}
