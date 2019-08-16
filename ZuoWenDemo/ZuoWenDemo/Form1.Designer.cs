namespace ZuoWenDemo
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_Load = new System.Windows.Forms.Button();
            this.tB_input = new System.Windows.Forms.TextBox();
            this.cLB_YaoSu = new System.Windows.Forms.CheckedListBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.rTBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // btn_Load
            // 
            this.btn_Load.Font = new System.Drawing.Font("宋体", 10F);
            this.btn_Load.Location = new System.Drawing.Point(1186, 339);
            this.btn_Load.Name = "btn_Load";
            this.btn_Load.Size = new System.Drawing.Size(80, 25);
            this.btn_Load.TabIndex = 1;
            this.btn_Load.Text = "分析作文";
            this.btn_Load.UseVisualStyleBackColor = true;
            this.btn_Load.Click += new System.EventHandler(this.btn_Load_Click);
            // 
            // tB_input
            // 
            this.tB_input.Font = new System.Drawing.Font("宋体", 12F);
            this.tB_input.Location = new System.Drawing.Point(493, 370);
            this.tB_input.Multiline = true;
            this.tB_input.Name = "tB_input";
            this.tB_input.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tB_input.Size = new System.Drawing.Size(773, 423);
            this.tB_input.TabIndex = 2;
            this.tB_input.Text = "这头牛全身披着黄褐色的毛，光滑油亮，头上长着一对镰刀似的角，真像一位威武的战士。它有两只圆圆的大眼睛，像灯泡似的，露出真诚憨厚的目光，让人觉得亲切无比。它高高的脊" +
    "梁，庞大的身躯，像一堵厚实的墙。它还有一条灵巧的长尾巴，是用来驱赶蚊蝇的。他好像在说，你好。我笑了一下。它又好像在说：“拜拜！”";
            // 
            // cLB_YaoSu
            // 
            this.cLB_YaoSu.Font = new System.Drawing.Font("宋体", 10F);
            this.cLB_YaoSu.FormattingEnabled = true;
            this.cLB_YaoSu.Location = new System.Drawing.Point(13, 86);
            this.cLB_YaoSu.Name = "cLB_YaoSu";
            this.cLB_YaoSu.Size = new System.Drawing.Size(458, 706);
            this.cLB_YaoSu.TabIndex = 4;
            this.cLB_YaoSu.SelectedIndexChanged += new System.EventHandler(this.cLB_YaoSu_SelectedIndexChanged);
            // 
            // comboBox1
            // 
            this.comboBox1.Font = new System.Drawing.Font("宋体", 10F);
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "状物",
            "写人",
            "写景",
            "记事"});
            this.comboBox1.Location = new System.Drawing.Point(13, 35);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(56, 21);
            this.comboBox1.TabIndex = 5;
            this.comboBox1.Text = "状物";
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // comboBox2
            // 
            this.comboBox2.Font = new System.Drawing.Font("宋体", 10F);
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "动物",
            "植物",
            "静物"});
            this.comboBox2.Location = new System.Drawing.Point(75, 35);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(56, 21);
            this.comboBox2.TabIndex = 5;
            this.comboBox2.Text = "动物";
            this.comboBox2.SelectedIndexChanged += new System.EventHandler(this.comboBox2_SelectedIndexChanged);
            // 
            // comboBox3
            // 
            this.comboBox3.Font = new System.Drawing.Font("宋体", 10F);
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Items.AddRange(new object[] {
            "一二年级",
            "二三年级",
            "三四年级",
            "四五年级",
            "五六年级"});
            this.comboBox3.Location = new System.Drawing.Point(166, 35);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(86, 21);
            this.comboBox3.TabIndex = 5;
            this.comboBox3.Text = "一二年级";
            this.comboBox3.SelectedIndexChanged += new System.EventHandler(this.comboBox3_SelectedIndexChanged);
            // 
            // comboBox4
            // 
            this.comboBox4.Font = new System.Drawing.Font("宋体", 10F);
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Items.AddRange(new object[] {
            "来历",
            "外形特点",
            "习性特点",
            "表达喜爱之情"});
            this.comboBox4.Location = new System.Drawing.Point(293, 35);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(86, 21);
            this.comboBox4.TabIndex = 5;
            this.comboBox4.Text = "习性特点";
            this.comboBox4.SelectedIndexChanged += new System.EventHandler(this.comboBox4_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 10F);
            this.label1.Location = new System.Drawing.Point(10, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(119, 14);
            this.label1.TabIndex = 6;
            this.label1.Text = "----- 主题 -----";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 10F);
            this.label2.Location = new System.Drawing.Point(191, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 14);
            this.label2.TabIndex = 6;
            this.label2.Text = "层级";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 10F);
            this.label3.Location = new System.Drawing.Point(304, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 14);
            this.label3.TabIndex = 6;
            this.label3.Text = "习作部分";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 10F);
            this.label4.Location = new System.Drawing.Point(817, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(140, 14);
            this.label4.TabIndex = 6;
            this.label4.Text = "--------信息-------";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 10F);
            this.label5.Location = new System.Drawing.Point(817, 345);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(168, 14);
            this.label5.TabIndex = 6;
            this.label5.Text = "--------我的作文-------";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("宋体", 10F);
            this.label6.Location = new System.Drawing.Point(147, 69);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(161, 14);
            this.label6.TabIndex = 6;
            this.label6.Text = "-------- 要 素 -------";
            // 
            // rTBox1
            // 
            this.rTBox1.Font = new System.Drawing.Font("宋体", 12F);
            this.rTBox1.Location = new System.Drawing.Point(493, 26);
            this.rTBox1.Name = "rTBox1";
            this.rTBox1.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.rTBox1.Size = new System.Drawing.Size(773, 307);
            this.rTBox1.TabIndex = 7;
            this.rTBox1.Text = "- Demo信息 -";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1278, 805);
            this.Controls.Add(this.rTBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBox4);
            this.Controls.Add(this.comboBox3);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.cLB_YaoSu);
            this.Controls.Add(this.tB_input);
            this.Controls.Add(this.btn_Load);
            this.Name = "Form1";
            this.Text = "作文神器Demo 0.52";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_Load;
        private System.Windows.Forms.TextBox tB_input;
        private System.Windows.Forms.CheckedListBox cLB_YaoSu;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.ComboBox comboBox4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.RichTextBox rTBox1;
    }
}

