using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace NLPLabel
{
    

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public List<Alog> AlogList = new List<Alog>();

        private void button1_Click(object sender, EventArgs e) // load file
        {
            OpenFileDialog fdlg = new OpenFileDialog();
            fdlg.Filter = "文本文件(*.txt)|*.txt";
            fdlg.Title = "载入待标注文本文件";
            if (fdlg.ShowDialog() == DialogResult.OK)
            {
                lb_fn.Text = fdlg.FileName;

                AlogList.Clear();
                listBox1.Items.Clear();

                string [] log_list = File.ReadAllLines(fdlg.FileName);

                int i=0;
                foreach (string lin in log_list)
                {
                    Alog al = new Alog(lin);
                    AlogList.Add(al);
                    string s1 = al.utxt+"\t" + al.rtxt;
                    s1 = i + ": " + s1;
                    i++;
                    listBox1.Items.Add(s1);
                }

                listBox1.SelectedIndex = 0;
            }
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox2.SelectedItem == null) return;

            listBox3.Items.Clear();
            string n_type = listBox2.SelectedItem.ToString();
            List<string> alist = action_dic[n_type];
            foreach (string action in alist)
            {
                listBox3.Items.Add(action + "（" + getActionNote(action) + "）");
            }

            textBox3.Text = n_type;
            textBox4.Text = "";
            label6.Text = "";
        }

        private void listBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox3.SelectedItem == null) return;

            string n_action = listBox3.SelectedItem.ToString();
            if(n_action.Contains("（"))
            {
                int p = n_action.IndexOf("（");
                n_action = n_action.Substring(0, p);
            }
            textBox4.Text = n_action;
            label6.Text = getActionNote(n_action);
        }

        public Dictionary<string, List<string>> action_dic = new Dictionary<string, List<string>>();
        public Dictionary<string, string> action_note = new Dictionary<string, string>();

        private string getActionNote(string action)
        {
            if(action_note.ContainsKey(action))  return action_note[action];
            return "";
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string action_cfg_path = @"qachild_domain_action.txt";
            string[] buf = File.ReadAllLines(action_cfg_path);

            action_dic.Clear();
            action_note.Clear();

            foreach (string lin in buf)
            {
                string[] tok = lin.Split('\t');
                string type = tok[0];
                //string action = tok[1] + "（" + tok[2] + "）";
                string action = tok[1];
                action_note[action] = tok[2];

                if (action_dic.ContainsKey(type))
                {
                    List<string> alist = action_dic[type];
                    alist.Add(action);
                }
                else
                {
                    List<string> alist = new List<string>();
                    alist.Add(action);
                    action_dic[type] = alist;
                }
            }

            foreach (string type in action_dic.Keys)
            {
                listBox2.Items.Add(type);
            }

        }

        private bool bValidEA(string ea)
        {
            if (ea == null) return false;
            if (ea == "") return false;
            if (ea == "-") return false;
            return true;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string txt = listBox1.SelectedItem.ToString();
            string[] tok = txt.Split(':');
            int idx = Int32.Parse(tok[0]);

            textBox5.Text = AlogList[idx].utxt;
            textBox7.Text = AlogList[idx].rtxt;

            string context = "";
            int i = idx - 1;
            while (i >= 0)
            {
                if (bValidEA(AlogList[i].ea))
                {
                    context = AlogList[i].utxt + "\r\n\t --- " +  AlogList[i].rtxt + "\r\n" + context;
                }
                else
                {
                    break;
                }
                i--;
            }

            textBox6.Text = context;

            textBox1.Text = AlogList[idx].type;
            textBox2.Text = AlogList[idx].action;
            label5.Text = getActionNote(AlogList[idx].action);

            textBox3.Text = AlogList[idx].n_type;
            textBox4.Text = AlogList[idx].n_action;
            label6.Text = getActionNote(AlogList[idx].n_action);

            listBox2.ClearSelected();
            listBox3.Items.Clear();

        }

        private void save_next()
        {
            if (listBox1.SelectedIndex == listBox1.Items.Count - 1)
            {
                MessageBox.Show("标注完成！！");
            }
            else
            {
                int idx = listBox1.SelectedIndex;
                AlogList[idx].n_type = textBox3.Text;
                AlogList[idx].n_action = textBox4.Text;

                listBox1.SelectedIndex++;
            }
            SaveFile();
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            save_next();
        }

        private void btnCorrect_Click(object sender, EventArgs e)
        {
            textBox3.Text = textBox1.Text;
            textBox4.Text = textBox2.Text;
            label6.Text = label5.Text;

            save_next();
        }


        private void SaveFile()
        {
            List<string> buf = new List<string>();
            foreach (Alog al in AlogList)
            {
                buf.Add(al.toLin());
            }
            File.WriteAllLines(lb_fn.Text, buf.ToArray(), Encoding.UTF8);
        }

        
    }
}
