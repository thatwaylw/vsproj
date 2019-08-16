using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
//using System.Collections.Generic;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private string bg_fn = "描红-梳.png";//@"C:\Users\laiwei\Desktop\描红-黑.png";
        private string cur_fn;

        private MH_data miaohong = new MH_data ();
        private int sta = 0;        // 0：笔画；1：填充
        private int i_fr = 0;     // 当前第几画frame
        private int i_fi = 0;     // 当前第几画fill


        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text = "haha哈";
            pictureBox1.ImageLocation = bg_fn;
            pictureBox1.Show();

            //#region 保存图片
            //Bitmap bmp = new Bitmap(pictureBox1.Image, pictureBox1.Width, pictureBox1.Height);
            //Graphics g = Graphics.FromImage(bmp);

            //bmp.Save("d://1.bmp", System.Drawing.Imaging.ImageFormat.Bmp);
            //#endregion

            //miaohong = new MH_data();
            sta = 0;
            button7.Text = "轮廓";
            i_fr = 0;
            i_fi = 0;
            numericUpDown1.Value = 0;
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            string x = e.X.ToString(); //x坐标
            string y = e.Y.ToString(); //Y坐标
            textBox1.Text = ("X:" + x + "  Y:" + y);

            if (e.Button == System.Windows.Forms.MouseButtons.Right)
            {// 但是，鼠标画上去的红点，取不到。。。取的还是白色
                Bitmap bmp = new Bitmap(pictureBox1.Image, pictureBox1.Width, pictureBox1.Height);
                Color color = bmp.GetPixel(e.X, e.Y);
                textBox1.Text = string.Format("{0},{1},{2}", color.R, color.G, color.B);
            }
            else
            {
                //Graphics g = ((PictureBox)sender).CreateGraphics();
                Graphics g = pictureBox1.CreateGraphics();

                if (sta == 0)
                {
                    g.FillEllipse(Brushes.Blue, e.X - 4, e.Y - 4, 8, 8);

                    List<Dot> dots = miaohong.GetcurFrame(i_fr);
                    dots.Add(new Dot(e.X, e.Y));
                }
                else
                {
                    List<Dot> dots = miaohong.GetcurFill(i_fi);
                    dots.Add(new Dot(e.X, e.Y));

                    if (dots.Count % 2 == 0)
                    {
                        Dot pre_dot = dots[dots.Count - 2];
                        Pen gPen = new Pen(Color.Blue, 1);
                        Point p1 = new Point(pre_dot.x, pre_dot.y);
                        Point p2 = new Point(e.X, e.Y);
                        g.DrawLine(gPen, p1, p2);

                        //密集补全。。。
                        if (dots.Count >= 4)
                        {
                            Dot a1 = dots[dots.Count - 4];
                            Dot b1 = dots[dots.Count - 3];
                            Dot a2 = dots[dots.Count - 2];
                            Dot b2 = dots[dots.Count - 1];

                            int dis_a = Dot.dist(a1, a2);
                            int dis_b = Dot.dist(b1, b2);
                            int max_dis = dis_a > dis_b ? dis_a : dis_b;
                            max_dis = (int)Math.Sqrt(max_dis);
                            int step = max_dis / 3;  // 按3个像素间隔补全

                            dots.RemoveRange(dots.Count - 2, 2);
                            for(int i=0; i<=step; i++)
                            {
                                int ax = a1.x + (a2.x - a1.x) * i / step;
                                int ay = a1.y + (a2.y - a1.y) * i / step;
                                dots.Add(new Dot(ax, ay));

                                int bx = b1.x + (b2.x - b1.x) * i / step;
                                int by = b1.y + (b2.y - b1.y) * i / step;
                                dots.Add(new Dot(bx, by));

                                g.DrawLine(gPen, new Point(ax, ay), new Point(bx, by));
                            }
                        }
                    }
                }
                g.Dispose();

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Graphics g = pictureBox1.CreateGraphics();
            Bitmap bmp = new Bitmap(pictureBox1.Image, pictureBox1.Width, pictureBox1.Height);
            for (int x = 0; x < pictureBox1.Width; x++)
            {
                for (int y = 0; y < pictureBox1.Height; y++)
                {
                    Color color = bmp.GetPixel(x, y);
                    if (color.R <= 200 && color.R >= 50)
                    {
                        g.FillEllipse(Brushes.Red, x, y, 2, 2);
                    }
                }
            }

            g.Dispose();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog fdlg = new OpenFileDialog();
            //fdlg.Filter = "文本文件(*.txt)|*.txt";
            //fdlg.Title = "载入待标注文本文件";
            if (fdlg.ShowDialog() == DialogResult.OK)
            {
                //textBox1.Text = fdlg.FileName;
                cur_fn = fdlg.FileName;
                //miaohong = new MH_data();
                miaohong.LoadfromFile(cur_fn);
                ShowMiaohong();
            }
            
        }

        private void button6_Click(object sender, EventArgs e)
        {
            miaohong.SavetoFile();
        }

        

        private void ShowMiaohong()
        {
            Graphics g = pictureBox1.CreateGraphics();
            //g.Clear(Color.White);
            //pictureBox1.Show();

            int idx = 0;
            foreach (List<Dot> dots in miaohong.frames)
            {
                foreach (Dot dot in dots)
                {
                    g.FillEllipse((sta==0 && i_fr==idx) ? Brushes.Red : Brushes.Gray, dot.x - 4, dot.y - 4, 8, 8);
                }
                idx++;
            }
            idx = 0;
            foreach (List<Dot> dots in miaohong.fills)
            {
                for (int i = 0; i + 1 < dots.Count; i += 2)
                {
                    Pen gPen = new Pen((sta == 1 && i_fi == idx) ? Color.Green : Color.Gray, 1);
                    Point p1 = new Point(dots[i].x, dots[i].y);
                    Point p2 = new Point(dots[i + 1].x, dots[i + 1].y);
                    g.DrawLine(gPen, p1, p2);
                }
                idx++;
            }
            g.Dispose();
        }


        private void button4_Click(object sender, EventArgs e)  //刷新
        {
            Graphics g = pictureBox1.CreateGraphics();
            g.Clear(Color.White);
            //pictureBox1.ImageLocation = bg_fn;
            //pictureBox1.Show();
            ShowMiaohong();

            //int ts = int.Parse(numericUpDown1.Value.ToString());
            //showFile(cur_fn, ts);
        }
        private void button5_Click(object sender, EventArgs e)  //加一笔
        {
            if (sta == 0)
            {
                i_fr++;
                List<Dot> dots = miaohong.GetcurFrame(i_fr);
                numericUpDown1.Value = i_fr;
            }
            else
            {
                i_fi++;
                List<Dot> dots = miaohong.GetcurFill(i_fi);
                numericUpDown1.Value = i_fi;
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if(sta==0)
            {
                sta = 1;
                button7.Text = "填充";
                numericUpDown1.Value = i_fi;
            }
            else
            {
                sta = 0;
                button7.Text = "轮廓";
                numericUpDown1.Value = i_fr;
            }
            ShowMiaohong();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {

            if (sta == 0)
            {
                i_fr = int.Parse(numericUpDown1.Value.ToString());
                if(i_fr>= miaohong.frames.Count)
                {
                    i_fr = miaohong.frames.Count - 1;
                    numericUpDown1.Value = i_fr;
                }
            }
            else
            {
                i_fi = int.Parse(numericUpDown1.Value.ToString());
                if(i_fi>= miaohong.fills.Count)
                {
                    i_fi = miaohong.fills.Count - 1;
                    numericUpDown1.Value = i_fi;
                }
            }

            ShowMiaohong();
        }


       
    }
}
