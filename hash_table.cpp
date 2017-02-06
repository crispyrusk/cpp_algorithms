///
/// Implementation of a simple hash table to store <string, string> pairs
/// Using open-address for collision resolution
///

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

class HashNode
{
public:
    HashNode() : key(""), value("") 
    {
    }
    
    HashNode(const string& keyArg, const string& valueArg)
        : key(keyArg), value(valueArg)
    {
    }

    string key;
    string value;

    friend ostream& operator<<(ostream& os, const HashNode& hashNode);
};

ostream& operator<<(ostream& os, const HashNode& hashNode)
{
    os << "(key: " << hashNode.key << ", value: " << hashNode.value << ")";
    return os;
}

class HashTable
{
public:
    HashTable(const int tableSize) : tableSize_(tableSize)
    {
        hashTable_.resize(tableSize_);
    }

    void insert(const string& key, const string& value)
    {
        assert(key.size() > 0); // empty keys not allowed
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
        hashTable_[openIndex] = HashNode(key, value);
    }

    HashNode get(const string& key)
    {
        assert(key.size() > 0);
        const int hashedKey = hashFunction_(key);
        assert(hashedKey >= 0 && hashedKey < tableSize_);
        if (hashTable_[hashedKey].key.size() == 0)
        {   // key not found
            std::cout << "key: " << key << " not found." << std::endl;
            return HashNode();
        }
        int matchedIndex = hashedKey;
        while (hashTable_[matchedIndex].key != key)
        {
            matchedIndex = (matchedIndex + 1) % tableSize_;
            if (matchedIndex == hashedKey || hashTable_[matchedIndex].key.size() == 0) 
            {
                std::cout << "key: " << key << " not found." << std::endl;
                return HashNode();
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

    int hashFunction_(const string& key)
    {
        return key.size() % tableSize_; // really simple hash function
    }

    const int tableSize_;
    vector<HashNode> hashTable_;
};

void testFn1()
{
    std::cout << "test1" << std::endl;
    auto ht = HashTable(3);
    ht.insert("foo", "first");
    ht.insert("bart", "second");
    ht.insert("bar", "third");
    ht.insert("blah", "fourth");
    ht.printTable();
}

void testFn2()
{
    std::cout << "test2" << std::endl;
    auto ht = HashTable(3);
    ht.insert("foo", "first");
    ht.insert("bart", "second");
    ht.printTable();
    std::cout << ht.get("bar") << std::endl;
}

void testFn3()
{
    std::cout << "test3" << std::endl;
    auto ht = HashTable(3);
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
    return 0;
}
