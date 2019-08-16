using System;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.Net;
using System.IO;
using System.Collections.Generic;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace ZuoWenDemo
{
    public partial class Form1 : Form
    {

        Dictionary<string, string> dic_jbys = new Dictionary<string, string>();       //本年级基本要素
        Dictionary<string, string> dic_yxys = new Dictionary<string, string>();       //本年级优秀要素
        Dictionary<string, string> dic_qtys = new Dictionary<string, string>();       //其他要素（层次基础+优秀排除以上两者的合集）

        public Form1()
        {
            InitializeComponent();
            
        }

        bool haveYaosu(string[] ysl, string ys)
        {
            foreach (string s in ysl)
            {
                if (ys.Equals(s))
                    return true;
            }
            return false;
        }

        private string genOtherYaoSu(string[] ys1, string[] ys2, string[] ys3, string[] ys4)
        {
            List<string> otheryaosu = new List<string>();
            foreach (string yaosu in ys1)
            {
                if (!haveYaosu(ys3, yaosu) && !haveYaosu(ys4, yaosu))
                    otheryaosu.Add(yaosu);
            }
            foreach (string yaosu in ys2)
            {
                if (!haveYaosu(ys3, yaosu) && !haveYaosu(ys4, yaosu))
                    otheryaosu.Add(yaosu);
            }
            string buf = "";
            foreach (string yaosu in otheryaosu)
            {
                buf += "【" + yaosu + "】";
            }
            return buf;
        }
        private string[] parseYaoSu(string buf)
        {
            buf = buf.Replace("】【", "|");
            buf = buf.Replace("【", "");
            buf = buf.Replace("】", "");

            return buf.Split('|');
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;

            string[] Yaosu_buf = File.ReadAllLines("yaosu.txt");
            foreach (string lin in Yaosu_buf)
            {
                string[] tok = lin.Split('\t');
                string key = tok[0] + "_" + tok[1] + "_" + tok[2];
                string yaosu1 = tok[3];     //层级基础要素
                string yaosu2 = tok[4];     //层级优秀要素
                string yaosu3 = tok[5];     //本年级基础要素
                string yaosu4 = tok[6];     //本年级优秀要素

                string otheryaosu = genOtherYaoSu(parseYaoSu(yaosu1), parseYaoSu(yaosu2), parseYaoSu(yaosu3), parseYaoSu(yaosu4));

                dic_jbys.Add(key, yaosu3);
                dic_yxys.Add(key, yaosu4);
                dic_qtys.Add(key, otheryaosu);
            }

            //string default_key = "状物-动物_一二年级_习性特点";
            RefreshYaosuList();
            
        }

        private string repText(string text)
        {
            return text.Replace(",", "，").Replace(".", "。").Replace("!", "！").Replace("?", "？").Replace("\"", "“").Replace("'", "‘").Replace(":", "：").Replace(";", "；");
        }
        
        JArray g_nlist = null;      // 储存本次分析结果的json对象

        private void btn_Load_Click(object sender, EventArgs e)
        {
            RefreshYaosuList();

            string key = comboBox1.Text + "-" + comboBox2.Text + "_" + comboBox3.Text + "_" + comboBox4.Text;
            tB_input.Text = repText(tB_input.Text);

            String url = "http://192.168.0.42:10121/qa_child/child_app/?toyId=9test50m&smode=ncourse-cnzuowen&t="+ tB_input.Text
                +"&sendpara=zuowen-cate&sendvalue=" + key;

            WebRequest request = WebRequest.Create(url);
            WebResponse response = request.GetResponse();
            StreamReader reader = new StreamReader(response.GetResponseStream(), Encoding.GetEncoding("utf-8"));
            String json = reader.ReadToEnd();
            //rTBox1.Text = json;
            //return;

            /*
            string jsonText = "{\"zone\":\"海淀\",\"zone_en\":\"haidian\"}";
            JObject jo = (JObject)JsonConvert.DeserializeObject(jsonText);
            string zone = jo["zone"].ToString();
            string zone_en = jo["zone_en"].ToString();   --*/

            JObject jo = (JObject)JsonConvert.DeserializeObject(json);
            JArray nlist = (JArray)jo["ncourse-list"];
            if (nlist == null)
                return;

            g_nlist = nlist;


            rTBox1.Text = "";

            int n = nlist.Count;
            for (int i = 0; i < n; i++)
            {
                if (nlist[i]["content"] == null)
                {
                    //tB_result.Text += nlist[i]["id"].ToString() + ": " + nlist[i]["zname"].ToString() + "\r\n";
                    rTBox1.Text += nlist[i]["zname"].ToString() + ": " + nlist[i]["flag"].ToString() + ": " + nlist[i]["keys"].ToString() + ": " + nlist[i]["ids"].ToString() + "\r\n";
                    //cLB_YaoSu.Items.Add(nlist[i]["ids"].ToString() + ": " + nlist[i]["zname"].ToString() + ": " + nlist[i]["flag"].ToString() + ": " + nlist[i]["keys"].ToString());
                }
                else
                {
                    rTBox1.Text += nlist[i]["zname"].ToString() + ": " + nlist[i]["flag"].ToString() + ": \r\n";
                    JArray clist = (JArray)nlist[i]["content"];
                    int k = clist.Count;
                    for (int j = 0; j < k; j++)
                    {
                        rTBox1.Text += "\t——" + clist[j]["keys"].ToString() + ": " + clist[j]["ids"].ToString() + "\r\n";
                    }
                }

                string[] tok = nlist[i]["flag"].ToString().Split('_');

                if (tok[1] == "无" || tok[1] == "不确定")
                    continue;

                for (int j = 0; j < cLB_YaoSu.Items.Count; j++)
                {
                    if (cLB_YaoSu.Items[j].ToString() == nlist[i]["zname"].ToString())
                    {
                        cLB_YaoSu.SetItemChecked(j, true);
                        cLB_YaoSu.Items[j] = nlist[i]["zname"].ToString() + "(" + tok[1] + ")";
                    }
                }
            }
        }

        private void RefreshYaosuList()
        {
            cLB_YaoSu.Items.Clear();

            string key = comboBox1.Text + "-" + comboBox2.Text + "_" + comboBox3.Text + "_" + comboBox4.Text;

            if (!dic_jbys.ContainsKey(key))
            {
                MessageBox.Show("暂不支持的组合！");
                return;

            }

            string[] jb_yaosu = parseYaoSu(dic_jbys[key]);
            string[] yx_yaosu = parseYaoSu(dic_yxys[key]);
            string[] qt_yaosu = parseYaoSu(dic_qtys[key]);  //取出的是otheryaosu
            //string[] yaosu4 = parseYaoSu(dic_yaosu4[key]);

            foreach (string yaosu in jb_yaosu)
            {
                cLB_YaoSu.Items.Add(yaosu);
            }
            cLB_YaoSu.Items.Add("--------------");
            foreach (string yaosu in yx_yaosu)
            {
                cLB_YaoSu.Items.Add(yaosu);
            }
            cLB_YaoSu.Items.Add("--------------");
            foreach (string yaosu in qt_yaosu)
            {
                cLB_YaoSu.Items.Add(yaosu);
            }
           
        }


        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            //int i_nianji = comboBox3.SelectedIndex;
            RefreshYaosuList();
        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
            RefreshYaosuList();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBox4.Items.Clear();
            if (comboBox2.Text == "动物")
            {
                comboBox4.Items.AddRange(new object[] {
                    "来历",
                    "外形特点",
                    "习性特点",
                    "表达喜爱之情"});
                comboBox4.Text = "来历";
            }
            else if (comboBox2.Text == "植物")
            {
                comboBox4.Items.AddRange(new object[] {
                    "来历",
                    "外形特点",
                    "属性与品格",
                    "结尾"});
                comboBox4.Text = "来历";
            }
            RefreshYaosuList();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            RefreshYaosuList();
        }

        private void showRichText(string keys, string ids, string sent)
        {
            //rTBox1.Clear();

            if (keys.Length <= 0 || ids.Length <= 0)
                return;

            string[] tok = keys.Split('_');
            string[] pos = ids.Split('_');

            if (tok.Length <= 0 || pos.Length <= 2)
                return;

            int ss = Int32.Parse(pos[0])/3;
            int ee = Int32.Parse(pos[pos.Length-1])/3;
            int pp = ss;

            //rTBox1.SelectionColor = Color.Black;
            rTBox1.AppendText(sent.Substring(0, ss));
            rTBox1.AppendText("【【【");
            //rTBox1.AppendText(sent.Substring(ss, ee - ss));
            for (int i = 1; i < pos.Length-1; i++ )
            {
                int ii = Int32.Parse(pos[i])/3;
                rTBox1.SelectionColor = Color.Black;
                rTBox1.AppendText(sent.Substring(pp, ii - pp));
                rTBox1.SelectionColor = Color.Red;
                rTBox1.AppendText(tok[i - 1]);
                pp = ii + tok[i - 1].Length;
            }
            rTBox1.SelectionColor = Color.Black;
            rTBox1.AppendText(sent.Substring(pp, ee - pp));
            rTBox1.AppendText("】】】");
            rTBox1.AppendText(sent.Substring(ee));
        }

        private void analyseYaosu(string type, string yaosuname)
        {
            int n = g_nlist.Count;
            for (int i = 0; i < n; i++)
            {
                //if (g_nlist[i]["flag"].ToString().Contains(type) && yaosuname.StartsWith(g_nlist[i]["zname"].ToString()))
                if (yaosuname.Equals(g_nlist[i]["zname"].ToString()))
                {
                    if (g_nlist[i]["content"] == null)
                    {
                        //rTBox1.Text = g_nlist[i]["keys"].ToString() + "\r\n\r\n" + g_nlist[i]["ids"].ToString();
                        showRichText(g_nlist[i]["keys"].ToString(), g_nlist[i]["ids"].ToString(), tB_input.Text);
                    }
                    else
                    {
                        JArray clist = (JArray)g_nlist[i]["content"];
                        int k = clist.Count;
                        for (int j = 0; j < k; j++)
                        {
                            showRichText(clist[j]["keys"].ToString(), clist[j]["ids"].ToString(), tB_input.Text);
                            rTBox1.AppendText("\r\n——————————————————————\r\n");
                        }
                    }
                    break;
                }
            }
        }

        private void cLB_YaoSu_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (g_nlist == null) return;
            rTBox1.Clear();
            //int idx = cLB_YaoSu.SelectedIndex;
            // if idx>xxx type=other; else if idx>xxx type=youxiu; else type=jichu
            string yaosuname = cLB_YaoSu.SelectedItem.ToString();
            int pp = yaosuname.IndexOf("(");
            if (pp > 0) yaosuname = yaosuname.Substring(0, pp);

            analyseYaosu("", yaosuname);
           
        }

               
    }
}
