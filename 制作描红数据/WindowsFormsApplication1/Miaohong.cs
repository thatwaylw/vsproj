using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace WindowsFormsApplication1
{
    class Dot
    {
        public int x;
        public int y;
        public Dot(int x0, int y0)
        {
            x = x0;
            y = y0;
        }
        static public int dist(Dot d1, Dot d2)
        {
            return (d1.x - d2.x) * (d1.x - d2.x) + (d1.y - d2.y) * (d1.y - d2.y);
        }
    }
    class MH_data
    {
        public List<List<Dot>> frames;
        public List<List<Dot>> fills;

        public MH_data()
        {
            frames = new List<List<Dot>>();
            fills = new List<List<Dot>>();
        }

        public List<Dot> GetLD(List<List<Dot>> LLD, int idx)
        {
            if(idx < LLD.Count)
            {
                return LLD[idx];
            }
            else
            {
                List<Dot> dots = new List<Dot>();
                LLD.Add(dots);
                return LLD[LLD.Count - 1];
            }
        }
        public List<Dot> GetcurFrame(int idx)
        {
            return GetLD(frames, idx);
        }
        public List<Dot> GetcurFill(int idx)
        {
            return GetLD(fills, idx);
        }

        public void LoadfromFile(string fn)
        {
            string buf = File.ReadAllText(fn);
            buf = buf.Replace("\n", "").Replace("\r", "");
            

            int p1 = buf.IndexOf("\"frame\":[[[") + 10;
            int p2 = buf.IndexOf("]]]", p1);
            string buf_frame = buf.Substring(p1, p2 - p1);
            frames = new List<List<Dot>>();

            p1 = buf.IndexOf("\"fill\":[[[") + 9;
            p2 = buf.IndexOf("]]]", p1);
            string buf_fill = buf.Substring(p1, p2 - p1);
            fills = new List<List<Dot>>();

            for (int i = 0; i < 2; i++)
            {
                string ss = (i == 0) ? buf_frame : buf_fill;

                ss = ss.Replace("]],[[", "|");
                ss = ss.Replace("],[", ";");
                ss = ss.Replace("[", "").Replace("]", "").Replace(" ", "");

                foreach (string bihua in ss.Split('|'))
                {
                    List<Dot> dots = new List<Dot>();

                    foreach (string ddot in bihua.Split(';'))
                    {
                        string[] tok = ddot.Split(',');
                        int x = int.Parse(tok[0]);
                        int y = int.Parse(tok[1]);

                        Dot n_dot = new Dot(x, y);
                        dots.Add(n_dot);

                    }
                    if (i == 0) frames.Add(dots);
                    else fills.Add(dots);
                }

            }
        }

        public void SavetoFile()
        {
            string buf = "{\"data\":[{\"pinyin\":\"a\",\"frame\":[\n";

            foreach (List<Dot> dots in frames)
            {
                buf += "[";
                foreach (Dot dot in dots)
                {
                    buf += string.Format("[{0},{1}],", dot.x, dot.y);
                }
                if (dots.Count>0)
                {
                    buf = buf.Remove(buf.Length - 1);
                }
                buf += "],\n";
            }
            if (frames.Count>0) buf = buf.Remove(buf.Length - 2);
            buf += "],\n\"fill\":[\n";

            foreach (List<Dot> dots in fills)
            {
                buf += "[";
                foreach (Dot dot in dots)
                {
                    buf += string.Format("[{0},{1}],", dot.x, dot.y);
                }
                if (dots.Count > 0)
                {
                    buf = buf.Remove(buf.Length - 1);
                }
                buf += "],\n";
            }
            if (fills.Count > 0) buf = buf.Remove(buf.Length - 2);
            buf += "],\n\"word\":\"考\",\"bihuashu\":6,\"gif\":null,\"obushou\":\"丷\",\"bihua_mingcheng\":\"点,撇,竖\"}],\"result\":\"succ\"}";

            File.WriteAllText("result.txt", buf);
        }
    }
    
}
