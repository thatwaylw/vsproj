using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace nlplogAna
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            WebClient wc = new WebClient();     //using System.Net;
            string result = wc.DownloadString("http://nlp.yuanqutech.com:18080/com_app/server_log/?service=qachild_app&num=1000&date=2015_08_01");
            //MessageBox.Show(result.Substring(0,100));


        }
    }
}
