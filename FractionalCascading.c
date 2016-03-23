#include<stdio.h>
#include<stdlib.h>

struct cas{
				int val,left,down;
				char type;
};

struct car{
				struct cas *ar;
				int cassz;
				struct car *next;
};

struct car *makecar(struct car *,int *,int);
void binsear(struct car *,int);
int main(){
				int *sz,**inps,i,j,k,l,n;
				struct car *head;
				printf("Enter the number of arrays : ");
				scanf("%d",&n);
				inps=(int **)malloc(sizeof(int *)*n);
				sz=malloc(sizeof(int)*n);
				for(i=0;i<n;i++){
								printf("Number of elements in array number %d ?\n",i+1);
								scanf("%d",sz+i);
								inps[i]=malloc(sizeof(int)*sz[i]);
								printf("Enter the elements : ");
								for(j=0;j<sz[i];j++){
												scanf("%d",inps[i]+j);
								}
				}
				head=(struct car *)malloc(sizeof(struct car));
				head->cassz=0;
				head->next=NULL;
				head->ar=NULL;
				for(i=n-1;i>=0;i--){
								head=makecar(head,inps[i],sz[i]);
				}
				printf("How many queries ?\n");
				scanf("%d",&i);
				while(i--){
								printf("Enter the value to search : ");
								scanf("%d",&j);
								binsear(head,j);
				}
				return 0;
}

struct car *makecar(struct car *lower,int *ar,int arsz){
				struct car *toret;
				struct cas *lar,*tar;
				int clef,alef,ci,ai,i;
				toret=(struct car *)malloc(sizeof(struct car));
				toret->next=lower;
				toret->cassz=arsz+((lower->cassz+1)>>1);
				toret->ar=(struct cas *)malloc(sizeof(struct cas)*(toret->cassz));
				ci=0;ai=0;i=0;
				clef=-1;alef=-1;
				lar=lower->ar;
				tar=toret->ar;
				while(ci<lower->cassz&&ai<arsz){
								if(ar[ai]<lar[ci].val){
												tar[i].val=ar[ai];
												tar[i].type=0;
												tar[i].left=clef;
												alef=i;
												ai++;
								}
								else{
												tar[i].val=lar[ci].val;
												tar[i].type=1;
												tar[i].left=alef;
												tar[i].down=ci;
												clef=i;
												ci+=2;
								}
								i++;
				}
				while(ai<arsz){
								tar[i].val=ar[ai];
								tar[i].type=0;
								tar[i].left=clef;
								ai++;
								i++;
				}
				while(ci<lower->cassz){
								tar[i].val=lar[ci].val;
								tar[i].type=1;
								tar[i].left=alef;
								tar[i].down=ci;
								ci+=2;
								i++;
				}
				if(i!=toret->cassz){
								printf("Improper cascade\nExpected size=%d\tSize obtained=%d\n",toret->cassz,i);
				}
				free(ar);
				return toret;
}

void binsear(struct car *head,int q){
				int i,j,k,psz,ansno;
				i=0;j=head->cassz-1;
				while(i<j){
								k=((i+j)>>1)+1;
								if(head->ar[k].val<=q){
												i=k;
								}
								else{
												j=k-1;
								}
				}
				if(head->ar[j].val<=q){
								i=j;
				}
				else{
								i=-1;
				}
				ansno=1;
				while(head->cassz>0){
								printf("\tLower bound in array number %d : ",ansno++);
								if(i+1<head->cassz&&head->ar[i+1].val<=q){
												i++;
								}
								if(i==-1){
												printf("None\n");
												head=head->next;
												continue;
								}
								if(head->ar[i].type==0){
												j=i;
												i=head->ar[i].left;
								}
								else{
												j=head->ar[i].left;
								}
								if(j==-1){
												printf("None\n");
								}
								else{
												printf("%d\n",head->ar[j].val);
								}
								if(i!=-1){
												i=head->ar[i].down;
								}
								head=head->next;
				}
}
