///
/// Implementation of a simple hash table to store <K, V> templated 
/// Only specialization implemented is <string, string>
/// Using open-address for collision resolution
///

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

template<typename K, typename V>
class HashNode
{
public:
    HashNode();
    
    HashNode(const K& keyArg, const V& valueArg)
        : key(keyArg), value(valueArg)
    {
    }

    K key;
    V value;

    // Syntax appears strange - friend template function - http://en.cppreference.com/w/cpp/language/friend
    template<typename K1, typename V1>
    friend ostream& operator<<(ostream& os, const HashNode<K1, V1>& hashNode);
};

// specialization of default constructor for <string, string>
template<>
HashNode<string, string>::HashNode()
{
    key = "";
    value = "";
}

// specialization friend operator<< for <string, string>
template<>
ostream& operator<<(ostream& os, const HashNode<string, string>& hashNode)
{
    os << "(key: " << hashNode.key << ", value: " << hashNode.value << ")";
    return os;
}

template<typename K, typename V>
class HashTable
{
public:
    HashTable(const int tableSize) : tableSize_(tableSize)
    {
        hashTable_.resize(tableSize_);
    }

    void insert(const K& key, const V& value)
    {
        const int hashedKey = hashFunction_(key);
        assert(hashedKey >= 0 && hashedKey < tableSize_);
        int openIndex = hashedKey;
        while (hashTable_[openIndex].key.size() > 0)
        {
            if (hashTable_[openIndex].key == key)
            {
                std::cout << "duplicated key " << key << "; skipping" << std::endl;
                return;
            }
            openIndex = (openIndex + 1) % tableSize_;
            if (openIndex == hashedKey)
            {   // cycled through
                std::cout << "no open address available ; skipping" << std::endl;
                return;
            }
        }
        hashTable_[openIndex] = HashNode<K, V>(key, value);
    }

    HashNode<K, V> get(const string& key)
    {
        assert(key.size() > 0);
        const int hashedKey = hashFunction_(key);
        assert(hashedKey >= 0 && hashedKey < tableSize_);
        if (hashTable_[hashedKey].key.size() == 0)
        {   // key not found
            std::cout << "key: " << key << " not found." << std::endl;
            return HashNode<K, V>();
        }
        int matchedIndex = hashedKey;
        while (hashTable_[matchedIndex].key != key)
        {
            matchedIndex = (matchedIndex + 1) % tableSize_;
            if (matchedIndex == hashedKey || hashTable_[matchedIndex].key.size() == 0) 
            {
                std::cout << "key: " << key << " not found." << std::endl;
                return HashNode<K,V>();
            }
        }
        return hashTable_[matchedIndex];
    }

    void printTable()
    {
        int index = 0;
        std::cout << "Internal Table\n==============" << std::endl;
        for (const auto& x : hashTable_)
        {
            std::cout << index++ << ":" << x << std::endl;
        }
    }



private:
    int hashFunction_(const string& key);

    const int tableSize_;
    vector< HashNode<K, V> > hashTable_;
};


// specialization for <string, string>
template<>
int HashTable<string, string>::hashFunction_(const string& key)
{
    return key.size() % tableSize_; // really simple hash function
}


void testFn1()
{
    std::cout << "test1" << std::endl;
    auto ht = HashTable<string, string>(3);
    ht.insert("foo", "first");
    ht.insert("bart", "second");
    ht.insert("bar", "third");
    ht.insert("blah", "fourth");
    ht.printTable();
}

void testFn2()
{
    std::cout << "test2" << std::endl;
    auto ht = HashTable<string, string>(3);
    ht.insert("foo", "first");
    ht.insert("bart", "second");
    ht.printTable();
    std::cout << ht.get("bar") << std::endl;
}

void testFn3()
{
    std::cout << "test3" << std::endl;
    auto ht = HashTable<string, string>(3);
    ht.insert("foo", "first");
    ht.insert("bart", "second");
    ht.printTable();
    std::cout << ht.get("bo") << std::endl;
}


int main(int argc, char** argv)
{
    testFn1();
    testFn2();
    testFn3();

    // auto ht = HashTable<int, string>(10); // compilation error - missing specialization

    return 0;
}
