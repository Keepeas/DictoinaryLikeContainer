#pragma once

/*
Container class to hold key, value pairs
Keeps track of inersertion order while keeping time complexity low:
Insertion O(1)
Delete    O(1)
Retreival O(1)


Acheived using a List to hold key/value pairs while keeping track of order
AND a hashtable to store a key/ListIterator to quickly find and execute within the list

Supports iteration & foreach style iteration
*/


#include<list>
#include<unordered_map>

template <class K, class V>
class Dict
{
private:
	//List to store pairs and keep insertion order
	std::list<std::pair<K,V>> OrderList;

	//HashTable to quickly find location within OrderList
	//std::unordered_map<K, std::list<std::pair<K, V>>>::iterator > LookUpMap;
	std::unordered_map<K, typename std::list<std::pair<K,V>>::iterator > LookUpMap;

public:
	void Insert(const K &key, const V &val)
	{
		if (LookUpMap.find(key) == LookUpMap.end())
		{
			OrderList.push_back(std::pair<K, V>(key, val));
			auto iter = OrderList.end();
			iter--;
			auto obj = std::pair<K, typename std::list<std::pair<K, V>>::iterator>(key, iter);
			LookUpMap.insert(obj);
		}
	}

	void Delete(const K &key)
	{
		auto iter = LookUpMap.find(key);
		if (iter != LookUpMap.end())
		{
			OrderList.erase(iter->second);
			LookUpMap.erase(iter);
		}
	}

	V Retrieve(const K& key) const
	{
		auto iter = LookUpMap.find(key);
		if (iter != LookUpMap.end())
		{
			if (iter->second != OrderList.end())
			{
				std::pair<K, V> p = *(iter->second);
				return p.second;
			}
		}
		return NULL;
	}

	typename std::list<std::pair<K, V>>::iterator begin()  
	{
		return OrderList.begin();
	}

	typename std::list<std::pair<K, V>>::iterator end() 
	{
		return OrderList.end();
	}


private:


};

