# ObjektinisVectorClass


## Funkcijų tikrinimas:

- push_back: - įdeda naują elementą i vektoriaus galą;
- swap: apkeičia du elementus vietomis;
- pop_back: panaikina paskutinį vektoriaus elementą;
- at(x): parodo elementą, esantį x pozicijoje;
- clear: visi vektoriaus elementai yra sunaikinami;


## Efektyvumo/Spartos analizė naduojant sukurtą vectorių ir biblioteką:

- Spartos analizė daryta naudojant Visual Studio;
- iki gegužės 19d. deadline nepataisiau "bad_alloc" erroro, kurį metė ir negaliu skaičiuoti 100m el. vektoriaus.
- Tolimesnius perskirstymo tyrimus bandysiu daryti su 10 mil. el, o vėliau taisysiu;

|        |  Sukurtas |   Senas   |
| ------ | --------- | -------   |
| 10k    | 0.0002609 | 0.00223   |
| 100k   | 0.0021731 | 0.0217749 |
| 1m     | 0.0214755 | 0.208617  |
| 10m    | 0.207067  | 2.09829   |
| 100m   |   ???     | 22.0518   | 
