int main(){


pid_t pid2, pid3, pid4;
pid2 = fork();

if(pid2 < 0){
	perror("Fehler beim Fork.\n");
	return EXIT_FAILURE;
}	

if(pid2 > 0){
	printf("Hallo ich bin der Vater von pid2.\n");
	pid3 = fork();
	if(pid3 > 0){
		printf("Hallo ich bin der Vater von pid3, der auch der Vater von pid2 ist.\n");
	}
	else{
		printf("Hallo ich bin pid3 an sich.\n");
		pid4 = fork();
		if(pid4 == 0){
			printf("Hallo ich bin pid4.\n");
		}
	}
}
else{
	printf("Hallo ich pid2 an sich.\n");
}



return 0;
}