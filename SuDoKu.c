#include<stdio.h>
#include<stdlib.h>
int mysqrt(int n);
int check(int);
void gogogo(int);
int **board,*toplace,size,unfilled,done=0;
int main(){
				int i;
				scanf("%d",&size);
				board=(int **)malloc(sizeof(int *)*size);
				for(i=0;i<size;i++)
								*(board+i)=(int *)malloc(sizeof(int)*size);
				for(i=0,unfilled=0;i<size*size;i++){
								scanf("%d",&board[i/size][i%size]);
								if(board[i/size][i%size]==0)
												unfilled++;
				}
				toplace=(int *)malloc(sizeof(int)*unfilled);
				for(i=0,unfilled=0;i<size*size;i++){
								if(board[i/size][i%size]==0){
												toplace[unfilled]=i;
												unfilled++;
								}
								else if(!check(i)){
												printf("-1\n");
												return 0;
								}
				}
				gogogo(0);
				if(done==0)
								printf("-1\n");
				return 0;
}

void gogogo(int index){
				int i;
				if(index==unfilled){
								done=1;
								for(i=0;i<size*size;i++){
												printf("%d ",board[i/size][i%size]);
												if(i%size==size-1)
																printf("\n");
								}
				}
				for(i=1;i<=size&&!done;i++){
								board[toplace[index]/size][toplace[index]%size]=i;
								if(check(toplace[index])){
												gogogo(index+1);
								}
				}
				if(!done)
								board[toplace[index]/size][toplace[index]%size]=0;
}

int check(int index){
				int x,y,val,i,j,boxx,boxy;
				x=index/size;
				y=index%size;
				val=board[x][y];
				boxx=x/mysqrt(size);
				boxx*=mysqrt(size);
				boxy=y/mysqrt(size);
				boxy*=mysqrt(size);
				for(i=0;i<size;i++){
								if(i!=x&&board[i][y]==val)
												return 0;
								if(i!=y&&board[x][i]==val)
												return 0;
				}
				for(i=0;i<mysqrt(size);i++)
								for(j=0;j<mysqrt(size);j++)
												if(((i+boxx)!=x||(j+boxy)!=y)&&board[i+boxx][j+boxy]==val)
																return 0;
				return 1;
}

int mysqrt(int n){
				int i;
				for(i=1;i*i<n;i++);
				return i;
}
