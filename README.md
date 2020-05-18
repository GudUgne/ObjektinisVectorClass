# ObjektinisVectorClass


## Funkcijų tikrinimas:

- push_back: - įdeda naują elementą i vektoriaus galą;

void push_back(value_type i){

		if (veksize + 1 > maxsize)
			alloc_new();
		array[veksize] = i;
		veksize++;
	};
  
- swap: apkeičia du elementus vietomis;

void swap(Vector<T>& other){
  
		size_t tvsize = veksize,
			tmaxsize = maxsize;
		T* tarray = array;

		veksize = other.veksize;
		maxsize = other.maxsize;
		array = other.array;

		other.veksize = tvsize;
		other.maxsize = tmaxsize;
		other.array = tarray;
	}
  
- pop_back: panaikina paskutinį vektoriaus elementą;

void pop_back(){
		veksize = veksize - 1;
		value_type* tmp = new value_type[maxsize];
		for (int i = 0; i < veksize; i++)
			tmp[i] = array[i];
		delete[] array;
		array = tmp;
	};
  
- at(x): parodo elementą, esantį x pozicijoje;

value_type at(int i){

		if (i < veksize)
			return array[i];
		throw std::out_of_range("out of range");
	};

- clear: visi vektoriaus elementai yra sunaikinami;

void clear(){

		veksize = 0;
		delete[] array;
		array = new value_type(maxsize);
	};

## Efektyvumo/Spartos analizė naudojant sukurtą vectorių ir biblioteką:

- Spartos analizė daryta naudojant Visual Studio;

|        |  Sukurtas |   Senas   |
| ------ | --------- | -------   |
| 10k    | 0.0002609 | 0.00223   |
| 100k   | 0.0021731 | 0.0217749 |
| 1m     | 0.0214755 | 0.208617  |
| 10m    | 0.207067  | 2.09829   |
| 100m   | 2.66802   | 22.0518   | 


## Spartos analizė naudojant sukurtą ir seną vektorius 2.0 užduotyje:

|        |  Sukurtas |   Senas   |
| ------ | --------- | -------   |
| 100k   | 	     | 26.0116	 |

- Įdėtas į 2.0 ver. naujas vektorius neveikė, toliau užduoties tęsti negalėjau;
