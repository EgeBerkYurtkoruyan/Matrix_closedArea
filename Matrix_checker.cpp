/***********************************************************************************
NAME: EGE BERK YURTKORUYAN
DATE: 17.02.2020

CS 204 --- HOMEWORK 1 

************************************************************************************/
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

bool find_area(vector<vector<char>> mat , int x , int  y, int z){

	/*******************************************************************************
	THE PURPOSE OF THIS FUNCTION IS TO RETURN TRUE IF THERE IS AN AREA OF 'x' IN THE MATRIX.

	ALSO, THIS FUNCTION PRINTS THE COORDINATES OF THE 'x' THAT ARE CONNECTED IF CALLED.

	THE VARIABLE 'direction' IS TO AVOID MOVING BACKWARDS IN THE FUNCTION.

	ALSO, THE LAST INTEGER INDEX IN THE FUNCTION IS TO DECIDE IF THE COORDINATES MUST BE PRINTED OR NOT
	IN ORDER TO PRINT OUT THE NECCESARY MESSAGE IF THE 'x' CHARACTERS MAKE A CLOSED AREA.
	********************************************************************************/

	int direction = 0;    // 1 = right , 2 = down , 3 = left , 4 = up

	int start_x = x , start_y = y;

	if (z != 0)
		cout << x << "\t" << y << endl;
	
		if		(y < mat[0].size()-1 && mat[x][y+1] == 'x'){
			direction = 1;
			y++;
		}else if (x < mat.size()-1 && mat[x+1][y] == 'x'){
			direction = 2;
			x++;
		}else if (y > 0 && mat[x][y-1] == 'x'){
			direction = 3;
			y--;
		}else if (x > 0 && mat[x-1][y] == 'x'){
			direction = 4;
			x--;
		}else 
			return false;
	

	while(start_x != x || start_y != y ){

		if (z != 0)
		  cout << x << "\t" << y << endl;

		if(direction == 1){
			
				if(y < mat[0].size()-1 && mat[x][y+1] == 'x' ){
				y++;
				}else if (x < mat.size()-1 && mat[x+1][y] ==  'x'){
				x++;
				direction = 2;
				}else if(x > 0 && mat[x-1][y] == 'x'){
				x--;
				direction = 4;
				}else
					return false;
			
		}else if (direction == 2){
				if ( x < mat.size()-1 && mat[x+1][y] ==  'x' ){
				x++;
				}else if ( y > 0 && mat[x][y-1] == 'x' ){
				direction = 3;
				y--;
				}else if( y < mat[0].size()-1 && mat[x][y+1] == 'x'){
				direction = 1;
				y++;
				}else
					return false;
			
		}else if (direction == 3){
			if (y > 0 && mat[x][y-1] == 'x'){
			y--;
			}else if (x > 0 && mat[x-1][y] == 'x'){
			direction = 4;
			x--;
			}else if (x < mat.size()-1 && mat[x+1][y] ==  'x'){
			direction = 2;
			x++;
			}else
				return false;

		}else if(direction == 4){
			if (x > 0 && mat[x-1][y] == 'x'){
			x--;
			}else if(y < mat[0].size()-1 && mat[x][y+1] == 'x'){
			direction = 1;
			y++;
			}else if (y > 0 && mat[x][y-1] == 'x'){
			direction = 3;
			y--;
			}else
				return false;
		}else{
			return false;
		}
	}

	
	if(start_x == x && y == start_y)
		return true;
	else 
		return false;
}

void printMatrix (vector<vector<char>> matrix){

	/*********************************************************************************
	THIS FUNCTION PRINTS THE MATRIX CHARACTER BY CHARACTER.
	************************************************************************************/
	cout << "Input Matrix:" << endl;

	int row = matrix.size() , column = matrix[0].size();

	for(int i = 0; i < row ; i++){
		for(int x = 0; x < column ; x++){
			cout << matrix[i][x] << " ";			// printing out the matrix with an order.
			}
			cout << "\n";
		}

}			

int main(){

	ifstream file;
	string filename , line ;
	char chars;

	
	do{

		cout << "Please enter file name: ";
		cin >> filename;

		file.open(filename.c_str());

		if(file.fail())
			cout << "Cannot find a file named " << filename << endl;

	} while (file.fail());

	vector<vector<char>> matrix;

	int previous_row = 0;

	while(getline(file,line)){
		vector<char> row_vector;
		stringstream ss(line);

		while(ss >> chars){
			row_vector.push_back(chars);

			if (chars != 'x' && chars != 'o'){						// this if statement will check the characters if they are only 'x' or 'o'. If they are not, the program will stop working with the message necessary.
				cout << filename << " includes invalid char(s)" << endl;
				return 0;
			}
		}

		if (previous_row != 0 && previous_row != row_vector.size()){
			cout << filename << " is invalid matrix, does not contain same amount of char each row!" << endl;
			return 0;
		
		}
		matrix.push_back(row_vector);
		previous_row = row_vector.size();
	}

	printMatrix(matrix);

	int row = matrix.size() , column = matrix[0].size();

	int x = 0, y = 0;

	do{											//THIS DO WHILE LOOP WILL GO ON UNTIL X == -1 AND Y == -1
		cout << "Please enter starting coordinates, first row X then column Y: " ;
		if(cin >> x && cin >> y){				//CHECK IF THE INPUTS ARE INTEGER OR NOT
			if (x == -1 && y == -1){
				cout << "Terminating..." << endl;
				return 0;
			}else if (x < -1 || y < -1 || x >= row || y >= column){
				cout << "Invalid Coordinates" << endl;
			}else if (matrix[x][y] == 'o'){
				cout << "This cell is not occupied!" << endl;
			}else{
				bool b = find_area(matrix,x,y,0);	//THIS FUNC RETURNS TRUE IF AN ENCLOSED AREA WAS FOUND.
				if(b)								
					cout << "Found an enclosed area. The coordinates of the followed path:" << endl;
				else
					cout <<  "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path:" << endl;
				find_area(matrix,x,y,1);
			}
				
		}else {							//IF THE INPUTS ARE NOT AN INT, THESE WILL PRINT THE ERROR MESSAGE AND CLEAR THE INPUT 
			cout << "Invalid Coordinates" << endl;
			string error;						
			cin.clear();
			cin >> error;
			cin.clear();
			cin >> error;
		}
	}while (x != -1 && y != -1);

return 0;
}
