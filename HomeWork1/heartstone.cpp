#include <iostream> 
#include <sstream>
#include <ctime>
#include <string>
#include <math.h>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "vector"
#include <map>
using namespace std;
using std::exit;
using std::cout;
using std::endl;
using std::string;
using std::stoi;
class CardManager
{
public:
	string _name, _class, _rarity, _set, _type, _cost;
};
void mergeSort(CardManager *array, int p, int r, string sortParam);
void merge(CardManager *arr, int p, int q, int r, string sortParam);
void sortedBy(CardManager *arr, int arrSize, string sortParam, string sortType);
void insertionSort(CardManager *arr, int arrSize, string sortParam);
int main(int argc, char** argv) {
	ifstream inputFile;
	string procedure, sortType, inputSet, outputSet;
	string line;

	CardManager* cardMng;

	string read;
	int k;
	sortType = argv[2];
	procedure = argv[1];
	inputSet = argv[3];
	outputSet = argv[4];
	inputFile.open(inputSet);
	string length = inputSet.substr(inputSet.find_last_of("-") + 1);
	int s = stoi(length.substr(0, length.length() - 5));
	switch (s) {
	case 1:
		cardMng = new CardManager[1000000];
		break;
	case 10:
		cardMng = new CardManager[10000];
		break;
	case 100:
		cardMng = new CardManager[100000];
		break;
	default:
		cardMng = new CardManager[1000000];
		break;
	}
	int i = 0;
	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		string token;
		int j = 0;
		while (std::getline(iss, token, '\t')) {
			switch (j) {
			case 0:
				cardMng[i]._name = token;
				break;
			case 1:
				cardMng[i]._class = token;
				break;
			case 2:
				cardMng[i]._rarity = token;
				break;
			case 3:
				cardMng[i]._set = token;
				break;
			case 4:
				cardMng[i]._type = token;
				break;
			case 5:
				cardMng[i]._cost = token;
				break;
			}

			j++;
		}
		i++;
	}
	inputFile.close();
	if (procedure == "-full") {
		sortedBy(cardMng, i, "_class", sortType);
		sortedBy(cardMng, i, "_cost", sortType);
		sortedBy(cardMng, i, "_name", sortType);
	}
	else if (procedure == "-filter") {
		sortedBy(cardMng, i, "_type", sortType);
	}
	ofstream myfile;
	myfile.open(outputSet);
	for (int k = 0; k < i; k++) {
		myfile << cardMng[k]._name << "\t" << cardMng[k]._class << "\t" << cardMng[k]._rarity << "\t" << cardMng[k]._set << "\t" << cardMng[k]._type << "\t" << cardMng[k]._cost << endl;
	}
	return 0;


}
void sortedBy(CardManager *arr, int arrSize, string sortParam, string sortType) {
	if (sortType == "-m") {
		mergeSort(arr, 0, arrSize, sortParam);
	}
	else {
		insertionSort(arr, arrSize, sortParam);
	}
}
void mergeSort(CardManager *arr, int p, int r, string sortParam) {

	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(arr, p, q, sortParam);
		mergeSort(arr, q + 1, r, sortParam);
		merge(arr, p, q, r, sortParam);
	}
	else return;
}

void merge(CardManager *arr, int p, int q, int r, string sortParam) {
	std::map<string, string> lt;
	std::map<string, string> rt;
	int n1 = (q - p) + 1;
	int n2 = (r - q);
	CardManager *left, *right;
	left = new CardManager[n1];
	right = new CardManager[n2];
	int i, j, k;
	for (i = 0; i < n1; i++) {
		left[i] = arr[(p + i)];
	}
	for (j = 0; j < n2; j++) {
		right[j] = arr[q + j + 1];
	}
	i = 0; j = 0, k = p;
	while (i < n1 && j < n2) {
		lt["_name"] = left[i]._name;
		lt["_class"] = left[i]._class;
		lt["_cost"] = left[i]._cost;
		lt["_type"] = left[i]._type;
		rt["_name"] = right[j]._name;
		rt["_class"] = right[j]._class;
		rt["_cost"] = right[j]._cost;
		rt["_type"] = right[j]._type;
		if (sortParam == "_cost" && lt[sortParam] != "" && rt[sortParam] != "") {
			if (stoi(lt[sortParam]) <= stoi(rt[sortParam])) {
				arr[k] = left[i];
				i++;
			}
			else {
				arr[k] = right[j];
				j++;
			}

		}
		else {
			if (lt[sortParam].compare(rt[sortParam]) == -1 || lt[sortParam].compare(rt[sortParam]) == 0) {
				arr[k] = left[i];
				i++;
			}
			else {
				arr[k] = right[j];
				j++;
			}
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = left[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = right[j];
		j++;
		k++;
	}
}
void insertionSort(CardManager *arr, int arrSize, string sortParam) {
	std::map<string, string> listArr;
	std::map<string, string> listKey;
	int i, j;
	CardManager key;
	for (j = 1; j < arrSize; j++) {
		key = arr[j];
		i = j - 1;
		listArr["_name"] = arr[i]._name;
		listArr["_class"] = arr[i]._class;
		listArr["_cost"] = arr[i]._cost;
		listArr["_type"] = arr[i]._type;
		listKey["_name"] = arr[j]._name;
		listKey["_class"] = arr[j]._class;
		listKey["_cost"] = arr[j]._cost;
		listKey["_type"] = arr[j]._type;
		if (sortParam == "_cost" && listArr[sortParam] != "" && listKey[sortParam] != "") {
			while (i > 0 && stoi(listArr[sortParam]) > stoi(listKey[sortParam])) {
				arr[i + 1] = arr[i];
				i--;
				listArr["_name"] = arr[i]._name;
				listArr["_class"] = arr[i]._class;
				listArr["_cost"] = arr[i]._cost;
				listArr["_type"] = arr[i]._type;
			}
		}
		else {
			while (i > 0 && listArr[sortParam].compare(listKey[sortParam]) == 1) {
				arr[i + 1] = arr[i];
				i--;
				listArr["_name"] = arr[i]._name;
				listArr["_class"] = arr[i]._class;
				listArr["_cost"] = arr[i]._cost;
				listArr["_type"] = arr[i]._type;
			}
		}
		arr[i + 1] = key;
	}
}