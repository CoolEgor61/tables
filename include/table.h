
#ifndef Table_h
#define Table_h

#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <algorithm>

template<typename T, typename CellType = std::pair<std::size_t, T>> class TableInterface
{
public:
	virtual bool insert(std::size_t key, const T& data) = 0;
	virtual bool erase(std::size_t key) = 0;
	virtual CellType find(std::size_t key) = 0;
	virtual size_t getSize() = 0;
	virtual bool isEmpty() = 0;
	virtual void clear() = 0;
};

template<typename T, typename CellType = std::pair<std::size_t,T>> class TableByArray: public TableInterface<T, CellType>
{
protected:
	std::vector<CellType> data;
	std::size_t size;
public:
	std::size_t getSize() override { return (this->size); };
	bool isEmpty() override { return ((this->size) == 0); };
	void clear() override { (this->data).clear(); (this->size) = 0; };
};

template<typename T, typename CellType = std::pair<std::size_t, T>> class UnorderedTable : public TableByArray<T, CellType>
{
public:
	UnorderedTable(std::size_t _size = 0, const std::vector<CellType>& _data = {})
	{
		(this->size) = _size;
		(this->data) = _data;
	};
	UnorderedTable(const UnorderedTable<T,CellType>& t)
	{
		(this->size) = t.size;
		(this->data) = t.data;
	};
	bool insert(std::size_t _key, const T& _data)
	{
		bool isExist = 0;
		for (std::size_t i = 0; i < (this->size); ++i)
		{
			if ((this->data)[i].first == _key)
			{
				isExist = 1;
				i = (this->size);
			}
		}
		if (!isExist)
		{
			(this->data).push_back(std::make_pair(_key, _data));
			++(this->size);
			return 1;
		}
		else return 0;
	}
	bool erase(std::size_t _key)
	{
		bool isExist = 0; std::size_t k;
		for (std::size_t i = 0; i < (this->size); ++i)
		{
			if ((this->data)[i].first == _key)
			{
				isExist = 1;
				k = i;
				i = (this->size);
			}
		}
		if (isExist)
		{
			std::swap((this->data)[k], (this->data)[(this->size) - 1]);
			(this->data).pop_back();
			--(this->size);
			return 1;
		}
		else return 0;
	}
	CellType find(std::size_t _key)
	{
		for (std::size_t i = 0; i < (this->size); ++i) if ((this->data)[i].first == _key) return (this->data)[i];
		throw std::logic_error("Key not found!");
	}
};

template<typename T, typename CellType = std::pair<std::size_t, T>> class OrderedTable : public TableByArray<T, CellType>
{
public:
	OrderedTable(std::size_t _size = 0, const std::vector<CellType>& _data = {})
	{
		(this->size) = _size;
		(this->data) = _data;
	};
	OrderedTable(const OrderedTable<T,CellType>& t)
	{
		(this->size) = t.size;
		(this->data) = t.data;
	};
	bool insert(std::size_t _key, const T& _data)
	{
		auto idx = std::lower_bound((this->data).begin(), (this->data).end(), std::make_pair(_key, T()), [](const CellType& a, const CellType& b) { return (a.first < b.first); });
		if (!(this->isEmpty())) { (this->data).insert(idx, std::make_pair(_key, _data)); ++(this->size); return 1; }
		else {
			(this->data).push_back(std::make_pair(_key, _data));
			++(this->size);
			return 1;
		}
		return 0;
	}
	bool erase(std::size_t _key)
	{
		auto idx = std::lower_bound((this->data).begin(), (this->data).end(), std::make_pair(_key, T()), [](const CellType& a, const CellType& b) { return (a.first < b.first); });
		if (idx!= (this->data).end()) { (this->data).erase(idx); --(this->size); return 1; }
		else return 0;
	}
	CellType find(std::size_t _key)
	{
		if (_key == (this->data)[(this->size)-1].first) return (this->data)[(this->size)-1];
		else {
			auto idx = std::lower_bound((this->data).begin(), (this->data).end(), std::make_pair(_key, T()), [](const CellType& a, const CellType& b) { return (a.first < b.first); });
			if (idx != (this->data).end() && (*idx).first==_key) return std::make_pair(_key, (*idx).second);
			else throw std::logic_error("Key not found!");
		}
	}
};

template<typename T, typename CellType = std::pair<int, std::pair<T, bool>>> class HashTableOpenMix : public TableByArray<T, CellType>
{
private:
	const std::size_t p = 14867, a = rand() * (p - 2) + 1, b = rand() * (p - 1);
public:
	HashTableOpenMix()
	{
		(this->size) = 0;
		(this->data).resize(p + 1024);
		for (int i=0;i<p+1024;i++) (this->data)[i].first = -1;
	}
	HashTableOpenMix(std::size_t _size, const std::vector<CellType>& _data)
	{
		(this->size) = _size;
		(this->data) = _data;
	};
	HashTableOpenMix(const HashTableOpenMix<T, CellType>& t)
	{
		(this->size) = t.size;
		(this->data) = t.data;
	};
	std::size_t HashFunction (std::size_t key) noexcept
	{
		return ((a * key + b) % p) % (p + 1024);
	}
	bool insert(std::size_t _key, const T& _data)
	{
		std::size_t index = this->HashFunction(_key);
		if ((this->data)[index].first == _key && (this->data)[index].second.first == _data) return 0;
		else if ((this->data)[index].first == -1) {
			(this->data)[index].first = _key; (this->data)[index].second.first = _data; (this->size)++;
			return 1;
		}
		else {
			index += 1;
			std::size_t k = 1;
			while ((this->size) < p+1024 && k < p + 1024)
			{
				if ((this->data)[index].second.second == 1 || (this->data)[index].first == -1) {
					(this->data)[index].first = _key; (this->data)[index].second.first = _data; (this->data)[index].second.second = 0; (this->size)++;
					k = p + 1024;
					return 1;
				}
				index++; k++;
				if (index == p + 1024) index = 0;
			}
			return 0;
		}
	}
	bool erase(std::size_t _key)
	{
		std::size_t index = this->HashFunction(_key);
		if ((this->data)[index].first == -1) return 0;
		else if ((this->data)[index].first == _key && (this->data)[index].second.second != 1) {
			(this->data)[index].second.second = 1; (this->size)--;
			return 1;
		}
		else {
			index += 1;
			std::size_t k = 1;
			while (k < p + 1024 && (this->data)[index].first != -1)
			{
				if ((this->data)[index].first == _key && (this->data)[index].second.second != 1) {
					(this->data)[index].second.second = 1; (this->size)--;
					k = p + 1024;
					return 1;
				}
				index++; k++;
			}
			return 0;
		}
	}
	CellType find(std::size_t _key)
	{
		std::size_t index = this->HashFunction(_key);
		if ((this->data)[index].first == -1) throw std::runtime_error("No cell found!");
		else if ((this->data)[index].first == _key && (this->data)[index].second.second != 1) return (this->data)[index];
		else {
			index += 1;
			std::size_t k = 1;
			while (k<p+1024 && (this->data)[index].first != -1)
			{
				if ((this->data)[index].first == _key && (this->data)[index].second.second != 1) return (this->data)[index];
				index++; k++;
			}
			throw std::runtime_error("No cell found!");
		}
	}
};

#endif 
