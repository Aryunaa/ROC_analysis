#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QApplication>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <QStandardItemModel>

#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QCoreApplication>


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

static QString t;


static QString aryuna; //глобальная переменная
static QString ar;
static QStandardItemModel k;
static QList<float > floatss;
static int str_kol;
static int stolb_kol;

static float ** matrix;//данные с диагнозом
static float *list1;
static float *list2;


static QList<float > massCOP;
static int * PH; static int * PD; static int * NH; static int * ND;
static float * Se;
static float * Spec;


void MainWindow::on_pushButton_clicked()
{
    //организация считывания, открытия и отображения
       QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                       tr("Text Files (*.csv);;C++ Files (*.cpp *.h);;Text Files (*.txt)"));

          if (fileName != "")
          {
              QFile file(fileName);
              if (!file.open(QIODevice::ReadOnly))
                {
                    QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                    return;
                }

              QTextStream in(&file);

             /*
              * не включать
              *  QTextEdit textEdit;
              textEdit.setText(in.readAll());
              textEdit.show();
              QFile file_out("file_out_perceptron.txt");
              не включать
             */

              /* не включать
                QString str;
                if (file_out.open(QIODevice::WriteOnly))
              {
                  QTextStream stream(&file_out);
                  str="this is a test";
                  stream << str.toUpper(); //Запишет-THIS IS A TEST теперь должно записать SOMETHING
                  file_out.close();
                  if (stream.status() != QTextStream::Ok)
                  {
                      qDebug() << "Ошибка записи файла";
                  }
              }
              не включать
             */




             csvModel = new QStandardItemModel();

             csvModel = new QStandardItemModel();

             // Создаём поток для извлечения данных из файла
             QTextStream intest(&file);


             // Считываем данные до конца файла
             QString metaline=intest.readLine();
             aryuna=metaline;
             // csvModel->setColumnCount(6);  //возвращайся сюда!!!
             //  QStringList wordList;
             //  wordList = file.readAll().split(QRegExp("[\r\n]"),QString::SkipEmptyParts); //reading file and splitting it by lines


             csvModel->setHorizontalHeaderLabels(QStringList()<<metaline.split(','));
             ui->tableView->setModel(csvModel); // Устанавливаем модель в таблицу


             // Открываем файл из ресурсов. Вместо данного файла
             // необходимо указывать путь к вашему требуемому файлу
             //QFile file("/home/1.csv");
             // if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
             //     qDebug() << "File not exists";
            //} else {


                      while (!intest.atEnd())
                        {
                             // ... построчно
                             QString line = intest.readLine();

                             // Добавляем в модель по строке с элементами
                             QList<QStandardItem *> standardItemsList;
                             // учитываем, что строка разделяется запятой на колонки
                             for (QString item : line.split(","))
                                {
                                    standardItemsList.append(new QStandardItem(item));
                                    floatss.append(item.toFloat());
                                    qDebug()<<floatss;

                                    //myMatr.append()

                                    // standardItemsList.append(new QStandardItem(floats[0]));

                                }


                             QVector <float> myVect;


                             //QVector2D <float> mine;

                             //int massive[4] = {1, 2, 3, 4};
                             //ar= new **int;


                             for(int i = 0; i < floatss.length(); i++)
                               {
                                   myVect.append(floatss[i]);

                                   qDebug() << "Value " << i << ": " << myVect.value(i)<<" "<<floatss[i];
                               }


                             //myVector.destruct();
                             csvModel->insertRow(csvModel->rowCount(), standardItemsList);
                             qDebug()<<csvModel->columnCount();//stolbtsi priznaki
                             qDebug()<<csvModel->rowCount();//stroki ,sample
                             int a = csvModel->columnCount();
                             int t ;t= csvModel->rowCount();
                             int b; b=t;

                             float ** mas = new float*[b];
                             for (int i = 0; i < b; i++)
                               {
                                    mas[i] = new float[a];
                               }

                             for (int i = 0; i < b; i++)
                               {
                                   for (int j=0;j<a;j++)
                                       {
                                           mas[i][j] = floatss[i*a+j];
                                           qDebug()<<mas[i][j];
                                        }

                                   qDebug()<<"end of sample";
                               }

                             //working with global matrix
                             str_kol=b;
                             stolb_kol=a;
                             matrix = new float*[str_kol];
                             for (int i = 0; i < str_kol; i++)
                               {
                                   matrix[i] = new float[stolb_kol];
                               }

                             for (int i = 0; i < str_kol; i++)
                               {
                                   for (int j=0;j<stolb_kol;j++)
                                       {
                                           matrix[i][j] = floatss[i*stolb_kol+j];
                                           qDebug()<<matrix[i][j];

                                       }
                               }


                             //deleting of massives
                             for (int i = 0; i < b; i++)
                               {
                                   delete [] mas[i];
                               }
                             delete [] mas;

                             //очищать память в этом месте было плохой идеей! больше этого не делать!!!
                             //qDeleteAll(floatss.begin(),floatss.end());
                             //floatss.clear();
                             //qDeleteAll(standardItemsList.begin(),standardItemsList.end());
                             //standardItemsList.clear();




                             //file.close();
                       }
           //хочу сделать манипуляцию с данными и индексацию, чтобы потом работать с массивами и матрицами ---->done
           //ar=(csvModel->index(2,3));
           qDebug()<<"end of intest";
           in.atEnd();
           intest.atEnd();


              file.close();
              qDebug()<<"file is closed";
          }
          else
          {qDebug()<<"no file!";}

          qDebug()<<"end of action_triggered";





}

void MainWindow::on_pushButton_2_clicked()
{

    list1 = new float [str_kol];
    list2 = new float [str_kol];

     for (int i = 0;i< str_kol;i++)
    {

        list1[i]=matrix[i][0];
        qDebug()<<"matrix0"<<matrix[i][0];
        qDebug()<<"list1"<<list1[i];

        qDebug()<<"______________________________";

        list2[i]=matrix[i][1];
        qDebug()<<"matrix1"<<matrix[i][1];
        qDebug()<<"list2"<<list2[i];




    }


     float minD;
     minD = minfunc(list2);
     qDebug()<<"minD "<<minD;


     float maxH;
     maxH=maxfunc(list1);
     qDebug()<<"maxH "<<maxH;

if(maxH>minD)
{     int k;k=0;
     for(int i=0;i<str_kol;i++)
     {
         if(list2[i]<=maxH)
         {k++;}
     }

     for(int i=0;i<str_kol;i++)
     {
         if(list1[i]>=minD)
         {k++;}
     }

     qDebug()<<"k - пересечения "<<k;
     float c;
     c=(maxH+minD)/(k*2);

     qDebug()<<"C "<<c;

     //делаем границу разделения COP1
     float COP1;
     //COP1= minD + c;
     COP1= minD;
     qDebug()<<"COP1 "<<COP1;
     int len; len=0;
     int j; j =0;


     while(COP1<maxH)
        {massCOP.append(COP1);
         COP1+=c;
         len++;j++;
        }
     qDebug()<<"massCOP "<<massCOP;
     qDebug()<<"len "<<massCOP.length();

     len = massCOP.length();
     //определяем PH,PD,NH,ND

     PH = new int [len];
     PD = new int [len];
     NH = new int[len];
     ND = new int [len];

     for(int i=0;i<len;i++)
        {PH[i]=0;
         PD[i]=0;
         NH[i]=0;
         ND[i]=0;

        }


     for(int i=0;i<len;i++)
        {//на здоровых
         for(int j = 0;j<str_kol;j++)
            {//отриц тест, здоров
             if((list1[j]>minD) && (list1[j]<massCOP[i]))
                {NH[i]++;}
             //положит тест, здоров
             if(list1[j]>massCOP[i])
                {PH[i]++;}
            }
         //на больных
         for(int j = 0;j<str_kol;j++)
            {//положит тест, болен
             if((list2[j]<maxH) && (list2[j]>massCOP[i]))
                {PD[i]++;}
             //отриц тест, болен
             if(list2[j]<massCOP[i])
                {ND[i]++;}
            }

        }

     for(int i =0;i<len;i++)
        {
         qDebug()<<"ND "<<ND[i]<<" ,i= "<<i;

        }

     for(int i =0;i<len;i++)
        {
         qDebug()<<"PD "<<PD[i]<<" ,i= "<<i;

        }

     for(int i =0;i<len;i++)
        {
         qDebug()<<"NH "<<NH[i]<<" ,i= "<<i;

        }
     for(int i =0;i<len;i++)
        {
         qDebug()<<"PH "<<PH[i]<<" ,i= "<<i;

        }




     //определяем оптимальную точку разделения (сумма PH и ND минимальна)
     int St,Sum, sumj; St=0;Sum=PH[0]+ND[0];
     float opt_COP;
     for(int j=1;j<len;j++)
        {
         St=PH[j]+ND[j];
         if(St<=Sum)
            {
             Sum=St; sumj = j; opt_COP=massCOP[j];
             qDebug()<<"PH+ND= "<<Sum<<" ,j = "<<j;
            }

        }
     qDebug()<<"optCOP "<<opt_COP;


     //расчет Se,Spec
     Se = new float [len];
     Spec = new float [len];
     for(int i=0;i<len;i++)
        {
         Se[i]=float(PD[i])/(float(PD[i])+float(ND[i]));
         Spec[i]=float(NH[i])/(float(NH[i])+float(PH[i]));
        }

     for(int i =0;i<len;i++)
        {
         qDebug()<<"Se "<<Se[i];

        }

     for(int i =0;i<len;i++)
        {
         qDebug()<<"Spec "<<Spec[i];

        }



   //вывод расчетов на экран
   QTextEdit *txt = new QTextEdit();
   txt->setFixedHeight(150);
   txt->setFixedWidth(300);


   QString cop_opt, j_opt ,sum_err, Spec_str, senc_str ;
   cop_opt = "Оптимальная граница разделения классов : ";
   cop_opt.append(QString::number(double(opt_COP)));
   j_opt = "номер точки : ";
   j_opt.append(QString::number(sumj));
   sum_err = "Сумма ошибок: ";
   sum_err.append(QString::number(Sum));
   Spec_str = "Специфичность: ";
   Spec_str.append(QString::number(double(Spec[sumj])));

   senc_str = "Чувствительность ";
   senc_str.append(QString::number(double(Se[sumj])));

   txt->setText("Проведенные расчеты:");
   txt->append(cop_opt);
   txt->append(j_opt);
   txt->append(sum_err);
   txt->append(Spec_str);
   txt->append(senc_str);
   txt->show();


}else
{ float COP1;
  COP1 = (maxH+minD)/2;
  QTextEdit *txt = new QTextEdit();
  txt->setFixedHeight(150);
  txt->setFixedWidth(300);
  txt->setText("Множества не пересекаются, оптимальная граница разделения классов: ");
  txt->append(QString::number(double(COP1)));
  txt->show();

}


}

float MainWindow::minfunc(float * list)
{   float mind;
    mind=list[0];
    for(int i=1;i<str_kol;i++)
        {if(list[i]<mind)
            {mind=list[i];

            }

        }
    return(mind);

}

float MainWindow::maxfunc(float * list)
{   float maxd;
    maxd=list[0];
    for(int i=1;i<str_kol;i++)
        {if(list[i]>maxd)
            {maxd=list[i];

            }

        }
    return(maxd);

}


void MainWindow::on_pushButton_3_clicked()
{


    for (int i=0;i<str_kol;i++)
        {delete [] matrix[i];


        }
    delete [] matrix;

    delete [] list1;
    delete [] list2;

    delete [] Se;
    delete [] Spec;
    delete [] PH;
    delete [] NH;
    delete [] PD;
    delete [] ND;

    qDebug()<<"successfull deleting and closing";

    QCoreApplication::quit();


}

void MainWindow::on_pushButton_4_clicked()
{
   int len; len = massCOP.length();
   double * no_sp;
   no_sp = new double [len];
   for(int i=0;i<len;i++)
    {
     no_sp[i]=1-double(Spec[i]);
    }

   //create graph and assign data to it:   1-sp =x, se = y

   //Вычисляем наши данные
       QVector<double> X(len), Y(len);
       for (int i =0;i<len;i++)
        {
         X[i]=no_sp[i];
         Y[i]=double(Se[i]);
        }

       ui->widget->addGraph();
       ui->widget->graph(0)->setData(X,Y);
       //x and y???

       // give the axes some labels:
       ui->widget->xAxis->setLabel("Неспецифичность");
       ui->widget->yAxis->setLabel("Чувствительность");

       // set axes ranges, so we see all data:
       ui->widget->xAxis->setRange(0,1);
       ui->widget->yAxis->setRange(0,1);
       ui->widget->replot();




       QTextEdit *txt = new QTextEdit();
       txt->setFixedHeight(150);
       txt->setFixedWidth(300);

       txt->setText("Площадь под кривой: ");
       double P1; P1=0;
       for(int i=0;i<(len-2);i++)
       {
           P1+= ((Y[i]+Y[i+1])/2)*fabs((X[i+1]-X[i]));
       }

       txt->append(QString::number(P1));
       txt->show();






}
