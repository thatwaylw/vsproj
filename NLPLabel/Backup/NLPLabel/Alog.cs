using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NLPLabel
{
    public class Alog
    {
        public string toyID;
        public string dt;
        public string sid;
        public string utxt;
        public string rtxt;
        public string ea;
        public string type;
        public string action;
        public string n_type;
        public string n_action;

        public Alog(string lin)
        {
            string[] tok = lin.Split('\t');
            if (tok.Length >= 8)
            {
                toyID = tok[0];
                dt = tok[1];
                sid = tok[2];
                utxt = tok[3];
                rtxt = tok[4];
                ea = tok[5];
                type = tok[6];
                action = tok[7];
            }
            if (tok.Length >= 9) n_type = tok[8];
            if (tok.Length >= 10) n_action = tok[9];
        }

        public string toLin()
        {
            return toyID + "\t" + dt + "\t" + sid + "\t" + utxt + "\t" + rtxt + "\t" + ea + "\t"
                + type + "\t" + action + "\t" + n_type + "\t" + n_action;
        }
    }
}
