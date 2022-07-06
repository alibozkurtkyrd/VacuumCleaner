#include<stdbool.h>  
#include <time.h>
struct Point
{
	int x;
	int y;
	bool active; // this is for possibilty list
	char mark; // if it is marked as "o" which means it is obstacle by obstacle or if it is marked by "t" which means that it is marked by trace list 
};
struct Point* createPosList(struct Point currentLocation)
{
	struct Point *posList = malloc(sizeof(struct Point)*4); //there are 4 possibilities for one point
	int x = currentLocation.x;
	int y = currentLocation.y;
	
	posList[0].x = x+1; posList[0].y = y;
	
	for (int i=0; i<4; i++) // basta tüm degerleri true yapıyoruz sonradan elendikçe false olacak
		posList[i].active=true;




	if (x != 0)	{
		posList[1].x = x-1; posList[1].y = y; // x degeri 0 dan kücük olmamalı buraa x != 0 dan x in sıfırdan kücük
						      // oldugu degeri anlamalıyız cünkü cihazı odanın köselerinden bırakıyoruz

	}

	else{
		posList[1].active = false; // if durumu çalışmaz ise 1 array elemanı defaul olarak 0,0 oldugu icin buna ihtiyac var
		posList[1].x = -777; posList[1].y= -777;
		posList[1].mark = 'o'; // yeni duvar var isede bu bir obstacle olmuş oluyor
	}

	posList[2].x = x; posList[2].y = y+1;

	if (y != 0) 
	{
		posList[3].x = x; posList[3].y = y-1; // y degeri 0 dan kücük olmamalı

	}

	else{
		posList[3].active = false;
		posList[3].mark = 'o';
		posList[3].x = -999; posList[3].y= -999;

	}

	return posList;
	
}

typedef struct {
  struct Point *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(struct Point));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, struct Point point) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(struct Point));
  }
  a->array[a->used++] = point;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

int printPointList(struct Point *list, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("list[%d] x,y: %d,%d\n", i, list[i].x, list[i].y);		
	}
	return 0;
}

int checkObstacleList(struct Point *posList, Array obstacle)
{
	// bu iç içe döngü sayesinde possibility listesiden obstacle listesindeki noktarı silmiş olacagız 
	// bu döngüyü buradan kaldırım  functions.h dosyasında bir adet fonksiyon olusturacagım
	for (int i = 0; i < 4; i++) // 4 posbList in boyutu
	{
		if (posList[i].active==true) // posList teki koordinatların aktif yani önceden listeler tarafında elenmemiş olması gerekiyor
		{
			for (int j=0; j < obstacle.used; j++)
			{

				//printf("(%d,%d) is element of posList\n", posList[i].x, posList[i].y);
				//printf("(%d,%d) is element of traceList\n", obstacle.array[j].x, obstacle.array[j].y);
				if ((posList[i].x == obstacle.array[j].x)&& (posList[i].y == obstacle.array[j].y))
				{
				
					posList[i].mark = 'o';
					posList[i].active = false;
					//printf("aktiflik durumu: %d\n", posList[i].active);
					printf("(%d,%d) is deleted from posssibility list due to OBSTACLE LIST\n", posList[i].x, posList[i].y);
				}
			}
			

		}

	}

	//printf("%d :", list[2].x);
	
}


int checkTraceList(struct Point *posList, Array trace)
{
	// bu iç içe döngü sayesinde possibility listesiden trace listesindeki noktarı silmiş olacagız 
	// bu döngüyü buradan kaldırım  functions.h dosyasında bir adet fonksiyon olusturacagım
	for (int i = 0; i < 4; i++) // 4 posbList in boyutu
	{
		if (posList[i].active==true) // posList teki koordinatların aktif yani önceden listeler tarafında elenmemiş olması gerekiyor
		{
			for (int j=0; j < trace.used; j++)
			{

				//printf("(%d,%d) is element of posList\n", posList[i].x, posList[i].y);
				//printf("(%d,%d) is element of traceList\n", trace.array[j].x, trace.array[j].y);
				if ((posList[i].x == trace.array[j].x)&& (posList[i].y == trace.array[j].y))
				{
					posList[i].active = false;
					posList[i].mark = 't';
					//printf("status of activate: %d\n", posList[i].active);
					printf("(%d,%d) is deleted from posssibility list due to TRACE LIST\n", posList[i].x, posList[i].y);
				}
			}
			

		}

	}

	//printf("%d :", list[2].x);
	
}

int checkDeviceSurrounded(struct Point *posList)
{
	int count = 0; // this calculate the number of marked field as "o" 
	// bu method sayesinde cihazın engeller ile cevrili olup olmadıgına bakacagız
	for (int i = 0; i < 4; i++) // 4 posbList in boyutu
	{
		if (posList[i].mark == 'o') // bu durum posListteki duvar ile ilgili olan kısımları iceriyor  
		{
			count++;
		}

	}
	//printf("checkDevice methodu count sayısı : \n", count);
	return count;	
}

int getInfoDistanceSensor(int size)
{
	if (size < 50)
		return 0;
	

	else 
		return 1;
}


struct Point randomSelection(struct Point *posList){
	
	int count = 0;// counts the number of active point in possList

	//int *randomArray = malloc(sizeof(int)*4);

	for (int i=0; i < 4; i++)
	{
		if (posList[i].active == true)
			count++;

	}
	printf("random selection method count value: %d\n", count);
	int *randomArray2 = malloc(sizeof(int)*count);
	//int count2 = count;	
	int count2 = 0;
	for (int i=0; i < 4; i++)
	{
		if (posList[i].active == true)
		{
			randomArray2[count2] = i; // posList in index numarasını kayıt ediyorum
			count2++;
		}
	}

	for (int i= 0; i<count; i++)
	{
		printf("index: %d and element %d \n", i, randomArray2[i]);
	}

	if (count != 0)
	{ // in this condition all around of current point surrounded which means it can not move anywhere
	 	srand(time(0));
		 int rand_num = rand() %count;
		 printf("random_num: %d\n ", rand_num);
		return posList[randomArray2[rand_num]];
	}

	else 
	{
		struct Point temp ;
		temp.x = -500; // eger temp yapısının x degeri -500 gibi bir deger ise (bunun posList te olusması imkansı) bu random işlemmini yapıl
			       // madıgı anlamına geliyor
		return temp;
	}
	
	// free yapmayı unutma
}

void movingForward()
{
	printf("moving forward\n");
}

void turnRight(int number)
{
	printf("%d times turn right\n",number);
}

void turnLeft(int number)
{
	printf("%d times turn left\n", number);
}




void detectDirection(struct Point selectedPoint, struct Point currentLocation, int *direction)
{
	int tempDirection;
	if(selectedPoint.x == currentLocation.x)
	{
		if(selectedPoint.y-currentLocation.y > 0)
			tempDirection = 1;
		else 
			tempDirection = 3;
	}

	else
	{
		
		if(selectedPoint.x-currentLocation.x > 0)
			tempDirection = 2;
		else 
			tempDirection = 4;
	}

	printf("temp direction: %d\n", tempDirection);

	int result=(tempDirection%4)-(*direction%4);

	if (result == 0) // && getInfoDistanceSensor(30) == 1)// burayı çıkarman gerek
	{
		tempDirection = *direction ; 
		
		printf("we can not move any direction \n");
	}
	else if (result < 0)
	{
		if (result == -1)
			turnLeft(1);

		else if (result == -2){

			turnLeft(2);
		}
		else 
			turnRight(1);
	}

	else
	{

		if (result == 1)
			turnRight(1);

		else if (result == 2){

			turnRight(2);
		}
		else 
			turnLeft(1);
	}

	*direction = tempDirection; // direction is updated
}


