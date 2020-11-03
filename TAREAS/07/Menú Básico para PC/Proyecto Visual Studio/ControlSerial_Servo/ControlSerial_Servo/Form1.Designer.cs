namespace ControlSerial_Servo
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.PuertoSerial = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Barra_ = new System.Windows.Forms.TrackBar();
            this.Bconexion = new System.Windows.Forms.Button();
            this.Tserial = new System.Windows.Forms.TextBox();
            this.Tvelocidad = new System.Windows.Forms.TextBox();
            this.TextoAngulo = new System.Windows.Forms.Label();
            this.AnguloPasos = new System.Windows.Forms.NumericUpDown();
            this.BtnEncender1 = new System.Windows.Forms.Button();
            this.BtnApagar1 = new System.Windows.Forms.Button();
            this.BtnEnciender2 = new System.Windows.Forms.Button();
            this.BtnApagar2 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.BtnSalir = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Barra_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnguloPasos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // PuertoSerial
            // 
            this.PuertoSerial.PortName = "COM8";
            // 
            // timer1
            // 
            this.timer1.Interval = 50;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(256, 135);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(146, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Control Servomotor";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(452, 190);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(33, 16);
            this.label2.TabIndex = 2;
            this.label2.Text = "180°";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(228, 190);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(19, 16);
            this.label3.TabIndex = 3;
            this.label3.Text = "0°";
            // 
            // Barra_
            // 
            this.Barra_.Cursor = System.Windows.Forms.Cursors.SizeWE;
            this.Barra_.Location = new System.Drawing.Point(248, 175);
            this.Barra_.Maximum = 180;
            this.Barra_.Name = "Barra_";
            this.Barra_.Size = new System.Drawing.Size(198, 45);
            this.Barra_.TabIndex = 5;
            this.Barra_.Value = 90;
            this.Barra_.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // Bconexion
            // 
            this.Bconexion.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Bconexion.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Bconexion.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Bconexion.Location = new System.Drawing.Point(87, 175);
            this.Bconexion.Name = "Bconexion";
            this.Bconexion.Size = new System.Drawing.Size(110, 50);
            this.Bconexion.TabIndex = 6;
            this.Bconexion.Text = "Conectar";
            this.Bconexion.UseVisualStyleBackColor = true;
            this.Bconexion.Click += new System.EventHandler(this.button1_Click);
            // 
            // Tserial
            // 
            this.Tserial.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Tserial.Location = new System.Drawing.Point(13, 175);
            this.Tserial.Name = "Tserial";
            this.Tserial.Size = new System.Drawing.Size(68, 24);
            this.Tserial.TabIndex = 7;
            this.Tserial.Text = "COM8";
            this.Tserial.TextChanged += new System.EventHandler(this.Tserial_TextChanged);
            // 
            // Tvelocidad
            // 
            this.Tvelocidad.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Tvelocidad.Location = new System.Drawing.Point(13, 201);
            this.Tvelocidad.Name = "Tvelocidad";
            this.Tvelocidad.Size = new System.Drawing.Size(68, 24);
            this.Tvelocidad.TabIndex = 8;
            this.Tvelocidad.Text = "9600";
            // 
            // TextoAngulo
            // 
            this.TextoAngulo.AutoSize = true;
            this.TextoAngulo.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.TextoAngulo.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextoAngulo.Location = new System.Drawing.Point(338, 210);
            this.TextoAngulo.Name = "TextoAngulo";
            this.TextoAngulo.Size = new System.Drawing.Size(22, 26);
            this.TextoAngulo.TabIndex = 9;
            this.TextoAngulo.Text = "0";
            // 
            // AnguloPasos
            // 
            this.AnguloPasos.Location = new System.Drawing.Point(27, 303);
            this.AnguloPasos.Maximum = new decimal(new int[] {
            1800,
            0,
            0,
            0});
            this.AnguloPasos.Name = "AnguloPasos";
            this.AnguloPasos.Size = new System.Drawing.Size(73, 20);
            this.AnguloPasos.TabIndex = 12;
            this.AnguloPasos.ValueChanged += new System.EventHandler(this.AnguloPasos_ValueChanged);
            // 
            // BtnEncender1
            // 
            this.BtnEncender1.Location = new System.Drawing.Point(248, 281);
            this.BtnEncender1.Name = "BtnEncender1";
            this.BtnEncender1.Size = new System.Drawing.Size(97, 23);
            this.BtnEncender1.TabIndex = 13;
            this.BtnEncender1.Text = "Enciende Led 1";
            this.BtnEncender1.UseVisualStyleBackColor = true;
            this.BtnEncender1.Click += new System.EventHandler(this.BtnEncender1_Click);
            // 
            // BtnApagar1
            // 
            this.BtnApagar1.Location = new System.Drawing.Point(371, 281);
            this.BtnApagar1.Name = "BtnApagar1";
            this.BtnApagar1.Size = new System.Drawing.Size(114, 23);
            this.BtnApagar1.TabIndex = 14;
            this.BtnApagar1.Text = "Apaga Led 1";
            this.BtnApagar1.UseVisualStyleBackColor = true;
            this.BtnApagar1.Click += new System.EventHandler(this.BtnApagar1_Click);
            // 
            // BtnEnciender2
            // 
            this.BtnEnciender2.Location = new System.Drawing.Point(248, 312);
            this.BtnEnciender2.Name = "BtnEnciender2";
            this.BtnEnciender2.Size = new System.Drawing.Size(97, 23);
            this.BtnEnciender2.TabIndex = 15;
            this.BtnEnciender2.Text = "Enciende Led 2";
            this.BtnEnciender2.UseVisualStyleBackColor = true;
            this.BtnEnciender2.Click += new System.EventHandler(this.BtnEnciender2_Click);
            // 
            // BtnApagar2
            // 
            this.BtnApagar2.Location = new System.Drawing.Point(371, 312);
            this.BtnApagar2.Name = "BtnApagar2";
            this.BtnApagar2.Size = new System.Drawing.Size(114, 23);
            this.BtnApagar2.TabIndex = 16;
            this.BtnApagar2.Text = "Apaga Led 2";
            this.BtnApagar2.UseVisualStyleBackColor = true;
            this.BtnApagar2.Click += new System.EventHandler(this.BtnApagar2_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(9, 135);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(184, 20);
            this.label4.TabIndex = 17;
            this.label4.Text = "Enlace de Comunicacion";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(23, 265);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(165, 20);
            this.label5.TabIndex = 18;
            this.label5.Text = "Control Motor a pasos";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(106, 310);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 13);
            this.label6.TabIndex = 19;
            this.label6.Text = "Grados";
            // 
            // BtnSalir
            // 
            this.BtnSalir.Location = new System.Drawing.Point(410, 355);
            this.BtnSalir.Name = "BtnSalir";
            this.BtnSalir.Size = new System.Drawing.Size(75, 23);
            this.BtnSalir.TabIndex = 20;
            this.BtnSalir.Text = "Salir";
            this.BtnSalir.UseVisualStyleBackColor = true;
            this.BtnSalir.Click += new System.EventHandler(this.BtnSalir_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.Location = new System.Drawing.Point(13, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(103, 108);
            this.pictureBox1.TabIndex = 21;
            this.pictureBox1.TabStop = false;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(145, 12);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(172, 24);
            this.label7.TabIndex = 22;
            this.label7.Text = "Control Servomotor";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(145, 48);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(241, 24);
            this.label8.TabIndex = 23;
            this.label8.Text = "Control de posición angular";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(507, 404);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.BtnSalir);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.BtnApagar2);
            this.Controls.Add(this.BtnEnciender2);
            this.Controls.Add(this.BtnApagar1);
            this.Controls.Add(this.BtnEncender1);
            this.Controls.Add(this.AnguloPasos);
            this.Controls.Add(this.TextoAngulo);
            this.Controls.Add(this.Tvelocidad);
            this.Controls.Add(this.Tserial);
            this.Controls.Add(this.Bconexion);
            this.Controls.Add(this.Barra_);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Servomotor y Motor de pasos";
            ((System.ComponentModel.ISupportInitialize)(this.Barra_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AnguloPasos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort PuertoSerial;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar Barra_;
        private System.Windows.Forms.Button Bconexion;
        private System.Windows.Forms.TextBox Tserial;
        private System.Windows.Forms.TextBox Tvelocidad;
        private System.Windows.Forms.Label TextoAngulo;
        private System.Windows.Forms.NumericUpDown AnguloPasos;
        private System.Windows.Forms.Button BtnEncender1;
        private System.Windows.Forms.Button BtnApagar1;
        private System.Windows.Forms.Button BtnEnciender2;
        private System.Windows.Forms.Button BtnApagar2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button BtnSalir;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
    }
}

