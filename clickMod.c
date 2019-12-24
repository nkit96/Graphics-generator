    #include<graphics.h>
    #include<stdio.h>
    #include<conio.h>
    #include<dos.h>

    union REGS i, o;
	//methods for
	int initmouse();
	void showmouseptr();
	void getmousepos(int *button, int *x, int *y);

  //methods for writing the code
  void initialCode(FILE *fp);
  void objectMethodCreator(FILE *fp);


  main()
  {
    char fname[20];
  	FILE *fp;

  	printf("Enter the filename.\n");
  	scanf("%s", fname);
  	fp=fopen(fname,"w+");

  	initialCode(fp);
  	objectMethodCreator(fp);
	getch();
  	//closing the file
  	fclose(fp);

    return 0;
  }

  void initialCode(FILE *fp)
  {
  //header file declaration
  	fputs("#include<stdio.h>\n",fp);
  	fputs("#include<conio.h>\n",fp);
  	fputs("#include<graphics.h>\n\n\n",fp);
  	//start of main method
    	fputs("void object(int x,int y);\n\n",fp);
  	fputs("int main(){\n",fp);
  	fputs("int x=1, y=1;\nint gd=DETECT, gm; \n",fp);
  	fputs("initgraph(&gd,&gm,\"C:\\\\turboc3\\\\bgi\");\n",fp);
  	fputs("object(x, y);\n",fp);


  	//end of main method
  	fputs("getch();\n",fp);
  	fputs("closegraph();\n",fp);
    	fputs("return 0;\n",fp);
  	fputs("}\n\n\n",fp);
  }


    void objectMethodCreator(FILE *fp)
    {
       int gd = DETECT, gm, status, button, x, y;
       char str[50];
       long int clicks=0;
       int xs,ys; //xsource  and ysource;

      //creating source code-----------
      tempfile=fopen("temp.txt","w+"); //tempfile to hold codes
      fputs("void object(int x, int y){\n",fp);


       initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

       status = initmouse();

       if ( status == 0 )
          printf("Mouse support not available.\n");
       else
       {
          showmouseptr();

          getmousepos(&button,&x,&y);

          while(!kbhit())
          {
             getmousepos(&button,&x,&y);

             if( button == 1 )
             {
                button = -1;
                if(!clicks)
                {
                  xs=x;
                  ys=y;
                }
                line(xs,ys,x,y);
                 //adding all including duplicate lines of code to a temp file
                fprintf(fp,"line(%d +x,%d +y,%d +x,%d +y);\n",xs,ys,x,y);
            
                xs=x;
                ys=y;
                clicks++;
             }
             else if( button == 2 )
             {
                button = -1;
                clicks=0;
             }

          }
       }
       //filtering duplicate line of code from temp file into main file;
       
       
       
       //closeing object method
       fputs("\n}",fp);
       
    }


    int initmouse()
    {
       i.x.ax = 0;
       int86(0X33, &i, &o);
       return ( o.x.ax );
    }

    void showmouseptr()
    {
       i.x.ax = 1;
       int86(0X33, &i, &o);
    }

    void getmousepos(int *button, int *x, int *y)
    {
       i.x.ax = 3;
       int86(0X33, &i, &o);

       *button = o.x.bx;
       *x = o.x.cx;
       *y = o.x.dx;
    }
