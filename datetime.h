
//=================cac ham thoi bat du kien thoi gian

char* GetSystemDate(){//lay ngay tu he thong 
	time_t curTime = time(0);//tra ve thoi gian theo lich cua he thong
	tm* now = localtime(&curTime);//tm la mot cau truc chua cac thong tin ve time
	char ch[11] = {0};
	sprintf(ch, "%d/%d/%d", now->tm_mday, now->tm_mon+1, 1900+now->tm_year);//year bat dau tu 1900 thang tu 0 den 11;
	return ch;
} 
        
 
// dung de so sanh ngay thang nam co lon hon nam hien tai hay khogn
int* SplitDate(char s[]){//di chuyen chuoi date sang mang de lam gi 
	int *a = new int[3]; //mang chu date time
	for(int i=0; i<3; i++) a[i] = -1;
	string txt;
	int index = 0;
	int n = strlen(s);

	for(int i=0; i<n; i++){
	//	cout<<"\nVong lap thu "<<i;
		if(s[i] == '/' || i == n-1){
			if(i == n-1) txt += s[i];
			int x = atoi(txt.c_str());
			a[index++] = x;
		//	cout<<"\nX ne: "<<x;
			txt = "";
		}else{
			txt += s[i];
		//	cout<<"\nelseTxt= "<<txt;
		}
	}
//	cout<<"\na ne: = "<<a[0]<<a[1]<<a[2];
	return a;//1832000
}
//
bool isLeapYear(int year){//bool nam nhuan
	if(year%400 == 0 || (year%4 == 0 && year%100 != 0)){
		return true;//nam nhuan
	}
	return false;
}
//
int DayOfMonth(int month, int year){
	if(month < 1 || month > 12) return 0;//k hop le
	
	switch(month){
		case 2:
			if(isLeapYear(year)) return 29;
			else return 28;
		case 4:
		case 6:
		case 9:
		case 11: return 30;
	}
	return 31;
}
// 
bool CheckDate(char* s){//check date co hop le hay k?
	int *a = SplitDate(s);//chu ngay 18032000
	bool res = true;// notice
	if(a[2] < 1900 || a[1] <= 0 || a[1] > 12 || a[0] <= 0) res = false;
	if(a[0] > DayOfMonth(a[1], a[2])) res = false;
	delete a;
	return res;
}
// 
time_t GetTime(char *s){//lay time tu he thong
	tm t;
	int *a = SplitDate(s);
	t.tm_year = a[2]-1900;
	t.tm_mon = a[1]-1;
	t.tm_mday = a[0];
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;
	time_t timer = mktime(&t);//tre ve time tuong ung cua cau truc

	delete a;
	return timer;
}


double DiffTime(char *time1, char *time2){//ham difTime dung de tinh toan su khac biet ve so giay cua time1 va time 2
	time_t t1 = GetTime(time1);
	time_t t2 = GetTime(time2);

	return difftime(GetTime(time1), GetTime(time2));
}

int CompareDate(char *date1, char *date2){//so sanh ngay muon va ngay tra
	int *a = SplitDate(date1);//mang con tro a chua timedate
	int *b = SplitDate(date2);
	
	if(a[2] < b[2]) return -1;
	else if(a[2] > b[2]) return 1;
	else{
		if(a[1] < b[1]) return -1;
		else if(a[1] > b[1]) return 1;
		else{
			if(a[0] < b[0]) return -1;
			else if(a[0] > b[0]) return 1;
			else return 0;
		}
	}
	return 0;
}
//ok



