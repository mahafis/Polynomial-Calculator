#include "polycalculator.h"
#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

LinkedList arr1;
LinkedList arr2;
LinkedList addArr;
LinkedList mulArr;
string poly1;
string poly2;

using namespace std;

int valid(string& input) {
	int count = 0;
	string temp;

	for (int i = 0; i < static_cast<int>(input.length()); i++) {
		if (input[i] != ' ') {
			temp += input[i];
		} //endif
	}//endfor

	input = temp;

	for (int i = 0; i < static_cast<int>(input.length()); i++) {

        if (input[i] != 'x' && input[i] != '^' && !isdigit(input[i]) && input[i] != '+' && input[i] != '-') {
          return -1;
        }

		if (input[i] == 'x') {
			if (input[i+1] != '^') {
				return -1;
			} //endif
			if (!isdigit(input[i-1])) {
				return -1;
			} //endif
			if (!isdigit(input[i+2])) {
				return -1;
			}
			if (input[i-1] == 0) {
				return -1;
			}
			if (input[i+2] < 0) {
				return -1;
			}
		}//endif
		if (input[i] == '+' || input[i] == '-') {
			if (!isdigit(input[i+1])) {
				return -1;
			} //endif
			if ((i != 0) && !isdigit(input[i-1])) {
				return -1;
			}//endif
		}//endif
	}//endfor
        return count;
}//endfunc


//calculator functions
void PolyCalculator::input() { //takes string input for parsing into our global lists
    arr1.removeAll();
    arr2.removeAll();
    addArr.removeAll();
	string temp1 = "";
	string temp2 = "";

	try {
		cout << "Enter first polynomial expression: ";
		getline(cin, temp1);
		cout << "Enter second polynomial expression: ";
		getline(cin, temp2);
	}catch (string e) {
		cout<<"Invalid Input"<<endl;
	}//endtry


	if ((valid(temp1) == -1) || (valid(temp2) == -1)) { // if there is no x in input, we ask again
		cout<<"Invalid"<<endl;
	} //endif

	else {
		poly1 = temp1;
		poly2 = temp2;
        parse(poly1, arr1);
        parse(poly2, arr2);
	}//endelse

    if (arr1.head == nullptr && arr2.head == nullptr) {
      cout<<"Invalid Input"<<endl;
    }

} //endfunc



void PolyCalculator::display(ostream &os) {
    cout << "Exp1: ";
	arr1.print();
    cout << "Exp2: ";
	arr2.print();
} //endfunc



void PolyCalculator::add() {
    addArr.removeAll();
	Node* temp1 = arr1.head;
	Node* temp2 = arr2.head;

    if (temp1 == nullptr || temp2 == nullptr) { // check for empty lists
      if (temp1 == nullptr) {
        arr2.print();
        return;
      }
      else if (temp2 == nullptr) {
        arr1.print();
        return;
      }

      else {
        cout << "0" << endl;
        return;
      }

    }

	while (true) { // if both not empty, add into new array and print that array
		addArr.insert(temp1->coef, temp1->expo);

        if (temp1->next == nullptr) {
          break;
        }//endif

		temp1 = temp1->next;
	}//endwhile

	while (true) { // adding arr2 elements into addarr
		addArr.insert(temp2->coef, temp2->expo);

        if (temp2->next == nullptr) {
          break;
        }//endif

		temp2 = temp2->next;
	}//endwhile

    if (addArr.head == nullptr) {
      cout << "0" << endl;
    }//endif

    else {
	addArr.print();
        }//endelse
}


bool PolyCalculator::parse(string expr, LinkedList& list) {
  string coeff;
  string expo;
	if (valid(expr)==0) {
		for (int i = 0; i < static_cast<int>(expr.length()); i++) { //finding coef of each term found based on x
			if (expr[i] == 'x') {
				for (int j = 1; j <= i+1; j++) {
					if ((expr[i-j] == '+') || (i-j < 0)) {
						coeff = expr.substr(i-j+1, j-1);
                        break;

					}//endif
					if (expr[i-j] == '-') {
						coeff = expr.substr(i-j, j);
                        break;

					}//endif
				}//endif
			}//endfor
			if (expr[i] == '^') { // finding exponents of each term found based on x

    			for (int j = 1; (i + j) <= static_cast<int>(expr.length()); j++) {
        			if ((i + j >= static_cast<int>(expr.length()) || (expr[i + j] == '+') || (expr[i + j] == '-'))) {
            		expo = expr.substr(i + 1, j - 1);
            		break;
                    } //endif
                }//endfor
                list.insert(stoi(coeff), stoi(expo)); // after we find the x's expo and coef, we insert them into our list
        }//endif
    }//endfor
    return true;
}//endif

    else {
          return false;
    }

}//endfunc


int PolyCalculator::degree(int expID) {

    // check if expID is valid (1 or 2)
    if (expID != 1 && expID != 2) {
        cout << "expID must be 1 or 2." << endl;
        return 0;
    }

    if (expID == 1) { // if input is 1, return exponent of the first node in list1
        if (arr1.head == nullptr) {
            cout << "First polynomial is empty." << endl;
            return 0;
        }
        return arr1.head->expo; // return the exponent of the first term in list1
    }

    if (expID == 2) { // if input is 2, return exponent of the first node in list2
        if (arr2.head == nullptr) {
            cout << "Second polynomial is empty." << endl;
            return 0;
        }
        return arr2.head->expo; // return the exponent of the first term in list2
    }

    return 0; // Default return, though this case will never be reached now
}


void PolyCalculator::isequal() {
	if (arr1 == arr2) {
		cout<<"both Polynomials are the same"<<endl;
	}
	else {
		cout<<"both Polynomials are different"<<endl;
	}

}

void PolyCalculator::mul() {
    // clear mulArr
    mulArr.removeAll();

    // check if any list is empty

    if (arr1.head == nullptr && arr2.head == nullptr) {
        std::cout << "Lists are empty." << std::endl;
        return;
    }

    if (arr1.head == nullptr || arr2.head == nullptr) {
        std::cout << "One of the lists is empty." << std::endl;
        return;
    }

    // traverse both lists
    Node* temp1 = arr1.head;
    while (temp1 != nullptr) {
        Node* temp2 = arr2.head;
        while (temp2 != nullptr) {
            // mult coefficients and add  exponents
            int newCoef = temp1->coef * temp2->coef;
            int newExpo = temp1->expo + temp2->expo;

            // add result into mulArr
            mulArr.insert(newCoef, newExpo);

            // move to next node in arr2
            temp2 = temp2->next;
        }
        // move to next node in arr1
        temp1 = temp1->next;
    }

    // print mularr
    mulArr.print();
}

int power(int base, int exp) {
  int result = base;
  while (exp > 1) {
    result*=base;
    exp--;
  }
  return result;
}

void PolyCalculator::evaluate(int expID, int x) {
  try {

  int eval = 0;

  if (expID == 1) { //evaluating polynomial 1

    if (arr1.head == nullptr) {
      cout << "First polynomial is empty."<<endl;
      return;
    }

    Node* temp = arr1.head;
    while (true) {
      eval = eval + temp->coef * power(x, temp->expo);
      if (temp->next == nullptr) {
        break;
      }//endif

      temp = temp->next;
    }//endwhile

    cout << "p(x) = ";
    arr1.print();
    cout << "p(" << x << ") = " << eval << endl;
    return;

  }//endif

  else if (expID == 2) { //evaluating polynomial 2

    if (arr2.head == nullptr) {
      cout << "First polynomial is empty."<<endl;
      return;
    }

    Node* temp = arr2.head;
    while (true) {
      eval += temp->coef * pow(x, temp->expo);

      if (temp->next == nullptr) {
        break;
      }//endif

      temp = temp->next;
    }//endwhile

    cout << "p(x) = ";
    arr2.print();
    cout << "p(" << x << ") = " << eval << endl;
    return;

  }//endif

  else {
    cout << "Invalid argument for evaluation" << endl;
  }//endelse
  }

  catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input for evaluation" << e.what() << std::endl;
    }

  catch (...) {
    std::cerr << "Invalid evaluation" << std::endl;
}

}//endfunc


void PolyCalculator::writeData(std::string path) {
    //creates an ostringstream to capture the output
    ostringstream captureStream;
    string temp1;

    // redirect std::cout to captureStream
    streambuf* originalCoutStream = cout.rdbuf();
    cout.rdbuf(captureStream.rdbuf());
    // call the function that prints strings


    cout << "Exp1: ";
    arr1.print();
    cout << "Exp2: ";
    arr2.print();
    cout << "Exp1 + Exp2 = ";
    add();
    cout << "Exp1 * Exp2 = ";
    mul();
    cout << "degree of Exp 1 is: ";
    cout << degree(1) << endl;
    cout << "degree of Exp 2 is: ";
    cout << degree(2) << endl;
    // restore original std::cout
    cout.rdbuf(originalCoutStream);
    temp1 = captureStream.str();

    // open a file to write the captured output
    ofstream outFile(path);

    // write the captured string to the file in one line
    if (outFile.is_open()) {
        outFile << temp1;
        outFile.close();
        cout << "Writing successful" << endl;
    }//endif
    else {
        cerr << "Unable to open the file!" << std::endl;
    }//endelse

}//endfunc



void PolyCalculator::readData(string path) {
   string temp1 = "";
   string temp2 = "";

  ifstream file(path); // open the file

    if (file.is_open()) {
        // read the first line into temp1
        if (!getline(file, temp1)) {
            cerr << "could not read the first line." << endl;
            return;
        }

        // read the second line into temp2
        if (!getline(file, temp2)) {
            cerr << "could not read the second line." << endl;
            return;
        }

        file.close(); // close the file when done
    } else {
        cerr << "Unable to open file." << endl;
    }


	if ((valid(temp1) == -1) || (valid(temp2) == -1)) { // if there is no x in input, we ask again
		cout<<"Invalid"<<endl;
	} //endif

	else {
		poly1 = temp1;
		poly2 = temp2;
        parse(poly1, arr1);
        parse(poly2, arr2);
	}//endelse

}//endfunc

