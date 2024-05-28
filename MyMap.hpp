#pragma once
template <typename T, typename U>
struct MyPair {
	T key;
	U value;
};
template <typename T, typename U>

class MyMap
{
public:
	MyMap();
	MyMap(const MyMap<T, U>& other);
	MyMap<T, U>& operator=(const MyMap<T, U>& other);
	~MyMap();
	void Print() const;
	void SetElem(const T& key, const U& value);
	void AddElem(const T& key, const U& value);
	void RemoveElem(const T& key);
	bool CheckForKey(const T& key) const;
	U GetValue(const T& key) const;
	MyPair& GetPair();
private:
	MyPair<T, U>* _data = nullptr;
	size_t capacity = 0;
	size_t size = 0;

	void free();
	void resize(size_t NewCap);
	void copyfrom(const MyMap<T, U>& other);

};

template<typename T, typename U>
 MyMap<T, U>::MyMap()
{
	capacity = 8;
	_data = new MyPair<T, U>[capacity];
}

template<typename T, typename U>
 MyMap<T, U>::MyMap(const MyMap<T, U>& other)
{
}

template<typename T, typename U>
 MyMap<T, U>& MyMap<T, U>::operator=(const MyMap<T, U>& other)
{
	if (this!+ &other) {
		free();
		copyfrom(other);

	}
	return *this;
}

template<typename T, typename U>
 MyMap<T, U>::~MyMap()
{
	free();
}

template<typename T, typename U>
 void MyMap<T, U>::Print() const
{
	 for (int i = 0; i < capacity; ++i) {
		 std::cout << _data[i].key << " " << _data[i].value;
		 std::endl;
	 }
}

template<typename T, typename U>
 void MyMap<T, U>::SetElem(const T& key, const U& value)
{
}

template<typename T, typename U>
 void MyMap<T, U>::AddElem(const T& key, const U& value)
{
	 if (CheckForKey(key)) {
		 throw std::error("Key is already added!");
	 }
	 if (size == capacity) {
		 resize();
	 }
	 int insertIndex = size;
	 for (int i = 0; i < size; i++) {
		 if (key < data[i].first) {
			 insertIndex = i;
			 break;
		 }
	 }
	 for (int i = size; i > insertIndex; i--) {
		 data[i] = data[i - 1];
	 }
	 data[insertIndex] = { key, value };
	 size++;
}

template<typename T, typename U>
 void MyMap<T, U>::RemoveElem(const T& key)
{
	 if (CheckForKey(key)) {
		 _data[key].value
	 }
}

template<typename T, typename U>
 bool MyMap<T, U>::CheckForKey(const T& key) const
{
	 for (int i = 0; i < size; ++i) {
		 if (key == _data[i]) {
			 return true;
		 }
	 }
	return false;
}

template<typename T, typename U>
U MyMap<T, U>::GetValue(const T& key) const
{
	if (CheckForKey(key)) {
		return _data[i].value;
	}
	else throw std::exception("key doesnt exist in the map");
}

template<typename T, typename U>
 MyPair& MyMap<T, U>::GetPair()
{
	// TODO: insert return statement here
}

template<typename T, typename U>
 void MyMap<T, U>::free()
{
	 delete[]_data;
	 capacity = 0;
	 size = 0;
}

template<typename T, typename U>
 void MyMap<T, U>::resize(size_t NewCap)
{
	 MyPair<T, U> temp = new MyPair[NewCap];
}

template<typename T, typename U>
 void MyMap<T, U>::copyfrom(const MyMap<T, U>& other)
{
	capacity = other.capacity;
	size = other.size();
	_data = new Pair<T, U>[capacity];
	for (int i = 0; i < capacity; i++) {
		_data[i] = other._data[i];
	}

}
