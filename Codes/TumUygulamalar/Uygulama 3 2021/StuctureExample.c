struct person{
	char *name ;
	char *surname;
	int age;
	char *sex;
	char *email;
};


int main() 
{
	char *person1name = "Fatmanur";
	char *person1surname = "Karapýçak";
	int person1age = 26;
	char *person1sex = "Female";
	char *person1email = "ftmnrkrp@yildiz.edu.tr";
	
	char *person2name = "Fatmanur";
	char *person2surname = "Karapýçak";
	int person2age = 26;
	char *person2sex = "Female";
	char *person2email = "ftmnrkrp@yildiz.edu.tr";
	//...
	
	struct person p1;
	p1.age = 25;
	
	printf("%d", p1.age);
	
	
	return 0; 
}
