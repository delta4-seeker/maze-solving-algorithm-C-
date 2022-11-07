#include <iostream>

#include <string>

#include <queue> // STL to implement priority queue

#include <unordered_map> // map data to key and value pair


using namespace std;

//node for huffman tree 
struct Node {
  char character; // character from input string 
  int frequency; // number of times the character is repeated 
  Node * left, * right;
};

// function to construct a node 
Node * createNode(char character, int frequency, Node * left, Node * right) {
  Node * node = new Node();

  node -> character = character;
  node -> frequency = frequency;
  node -> left = left;
  node -> right = right;

  return node;
}
// helper operator function to sort data in priority queue
struct compare {
  bool operator()(Node * left, Node * right) {
    return left -> frequency > right -> frequency;
  }
};

// recursive function to encode character into huffman code.
void encode(Node * root, string str,
  unordered_map < char, string > & huffmanCode) {
  if (root == nullptr)
    return;

  if (!root -> left && !root -> right) { // if left and right of the current node is not null
    huffmanCode[root -> character] = str;
  }
  // traverse from the root node till the leaf node using recursion function 
  encode(root -> left, str + "0", huffmanCode); // assign 0 lable to left node 
  encode(root -> right, str + "1", huffmanCode); // assign 1 lable to right node 
}
// recursive function to decode the huffman code into original character 
void decode(Node * root, int & index, string str) {
  //We start from root and do following until a leaf is found.

  if (root == nullptr) {
    return;
  }

  if (!root -> left && !root -> right) { //4. If during traversal, we encounter a leaf node, we print character of that
    //particular leaf node and then again continue the iteration of the encoded
    //data starting from step 1
    cout << root -> character;
    return;
  }

  index++;
  // traverse from the root node till the leaf node using recursion function 

  if (str[index] == '0') //2. If current bit is 0, we move to left node of the tree.
    decode(root -> left, index, str);
  else //3. If the bit is 1, we move to right node of the tree.

    decode(root -> right, index, str);
}
// generate huffman tree by initializing recursive function and print the output
void GenerateHuffmanTree(string input) {
  unordered_map < char, int > freq; // map the charater and its corresponsding frequency as key and value 
  for (char ch: input) { // calculate the frequecy for all character in "text" and store in map "freq"
    freq[ch]++;
  }

  priority_queue < Node * , vector < Node * > , compare > pq; // priority queue to store nodes and order according to 'compare' function 
  //  auto keyword specifies that the type of the variable that is being declared will be automatically deducted from its initializer.
  //in our case , pair will be of type map<char , int >
  for (auto pair: freq) { // for all the elements in 'freq' , create a node and push into 'pq' priority queue
    pq.push(createNode(pair.first, pair.second, nullptr, nullptr)); // pair.first represent key or map and pair.second represents value of map
  }
  // this loop is used to take two node from priority queue and add them to create a internal node 
  // this loop runs until there is one node remain in priority queue
  while (pq.size() != 1) {
    Node * left = pq.top();
    pq.pop(); // refer and remove the node with lowest frequency(highest priority)
    Node * right = pq.top();
    pq.pop(); // refer and remove the node with next lowest frequency(highest priority)

    int sum = left -> frequency + right -> frequency; // add the frequency and insert parent node to priority queue
    pq.push(createNode('\0', sum, left, right));
  }

  Node * root = pq.top(); // the parent key is root node and huffman tree is completed

  unordered_map < char, string > huffmanCode; // map the charater with the huffman code 
  //traverse the huffman tree and store the code to corresponding character in the map 
  encode(root, "", huffmanCode); // 

  cout << "Huffman Codes are :\n" << '\n';
  for (auto pair: huffmanCode) { // print the result 
    cout << pair.first << " " << pair.second << '\n';
  }

  cout << "\nOriginal string was :\n" << input << '\n';

  string str = "";
  for (char ch: input) {
    str += huffmanCode[ch];
  }

  cout << "\nEncoded string is :\n" << str << '\n';

  int index = -1;
  cout << "\nDecoded string is: \n";
  while (index < (int) str.size() - 2) {
    decode(root, index, str);
  }
}

int main() {
  string input = "Niraj Thapa"; // input  

  GenerateHuffmanTree(input);

  return 0;
}