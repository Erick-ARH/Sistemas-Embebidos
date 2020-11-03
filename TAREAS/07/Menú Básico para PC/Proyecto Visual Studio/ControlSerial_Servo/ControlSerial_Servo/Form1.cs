using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ControlSerial_Servo
{
    public partial class Form1 : Form
    {


        int[] dato = new int[3];
        byte[] enviarPort = new byte[1];
        Boolean FlagConexion = false;
        int Angulo;
        
        public Form1()
        {
            InitializeComponent();
            Angulo = Convert.ToInt32(Barra_.Value);
            TextoAngulo.Text = Convert.ToString(Angulo);
            TextoAngulo.Enabled = false;
            Barra_.Enabled = false;
        }




        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            Angulo = Convert.ToInt32(Barra_.Value);
            TextoAngulo.Text = Convert.ToString(Angulo);
            PuertoSerial.Write(Convert.ToString(Angulo)+ "\n");


        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            switch (FlagConexion)
            {
                case true:
                    timer1.Stop();
                    FlagConexion = false;
                    PuertoSerial.Close();
                    Bconexion.Text = "Conectar";

                    Barra_.Enabled = false;
                    TextoAngulo.Enabled = false;

                    break;
                case false:
                    timer1.Start();

                    FlagConexion = true;
                    PuertoSerial.PortName = Tserial.Text;
                    PuertoSerial.BaudRate = Convert.ToInt32(Tvelocidad.Text);
                    PuertoSerial.Open();
                    Bconexion.Text = "Desconectar";

                    Barra_.Enabled = true;
                    TextoAngulo.Enabled = true;
                    Angulo = Convert.ToInt32(Barra_.Value);
                    TextoAngulo.Text = Convert.ToString(Angulo);

                    PuertoSerial.Write(Convert.ToString(Angulo) + "\n");

                    break;
            }


        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int Angulo_Recibido;
            while (PuertoSerial.BytesToRead > 0)
            {
                
                dato[0] = PuertoSerial.ReadByte();
                if ((dato[2] == 255) && (dato[1] == 255))
                {
                    Angulo_Recibido =  dato[0];
                    if (Angulo_Recibido < 181)
                    {
                        Angulo = Angulo_Recibido;
                        TextoAngulo.Text = Convert.ToString(Angulo);
                        Barra_.Value =Convert.ToInt32(Angulo);
                    }
                }
              
                dato[2] = dato[1];
                dato[1] = dato[0];

            }
        }

        private void Tserial_TextChanged(object sender, EventArgs e)
        {

        }

       

       
        private void AnguloPasos_ValueChanged(object sender, EventArgs e)
        {
            PuertoSerial.Write(Convert.ToString(AnguloPasos.Value+200)+"\n");
        }

        private void BtnEncender1_Click(object sender, EventArgs e)
        {
            //int enciende1 = 190;
            //  PuertoSerial.Write() + "\n");
            PuertoSerial.Write("190\n");
        }

        private void BtnSalir_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void BtnApagar1_Click(object sender, EventArgs e)
        {
            PuertoSerial.Write("191\n");
        }

        private void BtnEnciender2_Click(object sender, EventArgs e)
        {
            PuertoSerial.Write("193\n");
        }

        private void BtnApagar2_Click(object sender, EventArgs e)
        {
            PuertoSerial.Write("194\n");
        }
    }
}
