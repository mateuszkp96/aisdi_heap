#include <iostream>
#include <vector>

using namespace std;

template<typename KeyType, typename ValueType>
class Heap3
{
    using KeyValueType = std::pair< KeyType, ValueType>;

    private:
    vector<KeyValueType> heap;
    int d = 3;

    int getParentIndex(int child) const
    {
        return (child - 1) / d;
    }

    int getKChildIndex(int parent, int k) const
    {
        return parent * d + k;
    }

    void heapifyUp(int i)
    {
        int parentIndex = getParentIndex(i);

        while(parentIndex >= 0)
        {
            if(heap[parentIndex].first > heap[i].first)
            {

                swap(heap[parentIndex], heap[i]);
                i = parentIndex;
                parentIndex = getParentIndex(i);
            }
            else {
                break;
            }
        }

    }

    void heapifyDown(int i)
    {
        int minIndex = i;
        int childIndex = getKChildIndex(i, 1);

        while(1) {
            minIndex = i;
            //szukanie najmniejszego dziecka
            for( ; childIndex < size() && childIndex <= getKChildIndex(i,d) ; ++childIndex)
            {
                if(heap[childIndex].first < heap[minIndex].first)
                {
                    minIndex = childIndex;
                }
            }

            // zamian
            if (minIndex == i){
                break;
            }
            else {
                swap(heap[minIndex], heap[i]);

                i = minIndex;
            }


        }


    }

    public:
    Heap3 () = default;

    bool isEmpty() const
    {
        return heap.empty();
    }

    void insert(KeyType const & key, ValueType const & value)
    {
        KeyValueType new_pair = make_pair(key,value);
        insert(new_pair);
    }

    void insert(KeyValueType const & key_value)
    {
        heap.push_back(key_value);
        heapifyUp(heap.size()-1);
    }

    KeyValueType const & peek() const
    {
        if(!isEmpty())
        {
            return heap[0];
        }
    }

    KeyValueType pop()
    {
        if(!isEmpty())
        {
            KeyValueType returnValue = heap[0];
            KeyValueType last = heap[heap.size() - 1];
            heap.pop_back();
            swap(heap[0], last);
            heapifyDown(0);
            return returnValue;
        }
    }

    size_t size() const
    {
        return heap.size();
    }

    void print(std::ostream& stream) const {
            printKElement(stream, 0, 0);
    }

    void printKElement(std::ostream& stream, int indent, int k) const{
        if (k >= heap.size()){
            return;
        }

        for (int i = 0; i < indent; ++i) {
            stream << '\t';
        }

        stream << heap[k].first <<endl;

        printKElement(stream, indent + 1, getKChildIndex(k, 1));
        printKElement(stream, indent + 1, getKChildIndex(k, 2));
        printKElement(stream, indent + 1, getKChildIndex(k, 3));
    }

};

int main()
{

    Heap3<int, int> heap;

    if (heap.isEmpty()) {
        cout << "Empty heap" << endl;
    }

    heap.insert(12,12);
    if (!heap.isEmpty()) {
        cout << "Not empty heap" << endl;
    }
    heap.pop();
    if (heap.isEmpty()) {
        cout << "Empty heap after pop" << endl;
    }

    heap.insert(12,12);
    heap.insert(5,5);

    heap.insert(34,34);

    heap.insert(25,25);

    heap.insert(7,7);

    heap.insert(101,101);
    heap.insert(9,9);
    heap.insert(29,29);
    heap.insert(42,42);
    heap.insert(152,152);



    cout << "\n\n Before pop \n";
    heap.print(cout);
    cout << endl;

    heap.pop();
    cout << "\n\n After pop \n";
    heap.print(cout);

    cout << "\n\n Before peek \n";
    heap.print(cout);
    cout << endl;

    heap.peek();
    cout << "\n\n After peek \n";
    heap.print(cout);

    cout << endl;
    heap.insert(0,0);
    heap.print(cout);




    return 0;
}
