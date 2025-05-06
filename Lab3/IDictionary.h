#pragma once

template <typename Tkey, typename Tvalue>
class IDictionary {
public:
	virtual int GetCount() const = 0;

	virtual int GetCapacity() const = 0;

	virtual Tvalue& Get(const Tkey& key) const = 0;

	virtual bool ContainsKey(const Tkey& key) const = 0;

	virtual void Add(std::pair<Tkey, Tvalue> record) = 0;

	virtual void Remove(const Tkey& key) = 0;
};