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
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace ZuoWenShenQi
{
    public partial class Form2 : Form
    {
        public Form1 F1 = null;//在窗体2中将窗体1实例化出来
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            //F1.Close(); //关闭窗体2时窗体1关闭
            F1.Show(); //关闭窗体2时窗体1重现
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void btn_dianping_Click(object sender, EventArgs e)
        {
            String url = "http://47.100.117.250:18271/qa_child/child_app/?toyId=9test50m&smode=ncourse-cnzuowen&t=" + tB_input.Text;
            WebRequest request = WebRequest.Create(url);
            WebResponse response = request.GetResponse();
            StreamReader reader = new StreamReader(response.GetResponseStream(), Encoding.GetEncoding("utf-8"));
            string jsonText = reader.ReadToEnd();

            JObject jo = (JObject)JsonConvert.DeserializeObject(jsonText);
            JArray nlist = (JArray)jo["ncourse-list"];

            cLB_YaoSu.Items.Clear();

            int n = nlist.Count;
            for (int i = 0; i < n; i++)
            {
                cLB_YaoSu.Items.Add(nlist[i]["id"].ToString() + ": " + nlist[i]["name"].ToString());
            }
        }
    }
}
