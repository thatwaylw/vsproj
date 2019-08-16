using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatLabel
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private string[] log_list = null;
        private List<string> rec_list = new List<string> ();

        private void btnOpen_Click(object sender, EventArgs e)
        {
            log_list = File.ReadAllLines("chatdata.txt");
            foreach (string lin in log_list)
            {
                listBox1.Items.Add(lin);
            }

            string qq = "";
            string aa = "";
            foreach (string lin in log_list)
            {
                if (lin.Length < 2)
                {
                    qq = qq.Trim('#');
                    aa = aa.Trim('#');
                    if(qq.Length>0 && aa.Length>0)
                        rec_list.Add(qq + "$" + aa);
                    qq = "";
                    aa = "";
                }
                else
                {
                    string[] tok = lin.Split('\t');
                    qq += "#" + tok[0];
                    aa += "#" + tok[1];
                }
            }
            qq = qq.TrimStart('#');
            aa = aa.TrimStart('#');
            if (qq.Length > 0 && aa.Length > 0)
                rec_list.Add(qq + "$" + aa);

            //foreach (string lin in rec_list)
            //{
            //   listBox2.Items.Add(lin);
            //}
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string txt = listBox1.SelectedItem.ToString();

            if(txt.Contains("\t"))
            {
                int p = txt.IndexOf("\t");
                txt = txt.Substring(0, p);
            }

            textBox1.Text = txt;
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            String kw = textBox1.SelectedText;
            label1.Text = kw;

            if (kw.Length <= 0) return;

            listBox2.Items.Clear();

            foreach (string lin in rec_list)
            {
                string[] tok = lin.Split('$');
                string qq = tok[0];
                string aa = tok[1];
                if(qq.Contains(kw))
                {
                 //   listBox2.Items.Add(lin);
                    listBox2.Items.Add(qq.Replace("#", " / "));
                    listBox2.Items.Add("\t\t" + aa.Replace("#", " / "));
                    listBox2.Items.Add("");
                }
            }
        }
    }
}
