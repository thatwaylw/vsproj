using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZuoWenShenQi
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Image img1, img2;

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Visible = false;
            button2.Visible = false;
            button3.Visible = false;
            //pictureBox1.Visible = false;
            img1 = Properties.Resources._1;
            img2 = Properties.Resources._2;
            //img1 = Image.FromFile("1.png");
            //img2 = Image.FromFile("2.png");
        }

        private void lB_leibie_SelectedIndexChanged(object sender, EventArgs e)
        {
            int ii = lB_leibie.SelectedIndex;
            if (ii == 4)
            {
                button1.Visible = true;
                button2.Visible = true;
                button3.Visible = true;
                //pictureBox1.ImageLocation = "1.png";
                pictureBox1.Image = img1;
            }
            else
            {
                button1.Visible = false;
                button2.Visible = false;
                button3.Visible = false;
                //pictureBox1.ImageLocation = "2.png";
                pictureBox1.Image = img2;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 f2 = new Form2();
            f2.Show();
            this.Hide();
            f2.F1 = this;
        }
    }
}
