namespace MorphingAlgorithm
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panelStart = new System.Windows.Forms.Panel();
            this.panelFinish = new System.Windows.Forms.Panel();
            this.labelStart = new System.Windows.Forms.Label();
            this.labelFinish = new System.Windows.Forms.Label();
            this.buttonStart = new System.Windows.Forms.Button();
            this.buttonFinish = new System.Windows.Forms.Button();
            this.panelStep = new System.Windows.Forms.Panel();
            this.buttonStep = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // panelStart
            // 
            this.panelStart.Location = new System.Drawing.Point(12, 12);
            this.panelStart.Name = "panelStart";
            this.panelStart.Size = new System.Drawing.Size(374, 388);
            this.panelStart.TabIndex = 0;
            this.panelStart.Click += new System.EventHandler(this.PanelStart_Click);
            // 
            // panelFinish
            // 
            this.panelFinish.Location = new System.Drawing.Point(392, 12);
            this.panelFinish.Name = "panelFinish";
            this.panelFinish.Size = new System.Drawing.Size(374, 388);
            this.panelFinish.TabIndex = 1;
            this.panelFinish.Click += new System.EventHandler(this.PanelFinish_Click);
            // 
            // labelStart
            // 
            this.labelStart.AutoSize = true;
            this.labelStart.Location = new System.Drawing.Point(12, 407);
            this.labelStart.Name = "labelStart";
            this.labelStart.Size = new System.Drawing.Size(35, 13);
            this.labelStart.TabIndex = 2;
            this.labelStart.Text = "label1";
            // 
            // labelFinish
            // 
            this.labelFinish.AutoSize = true;
            this.labelFinish.Location = new System.Drawing.Point(389, 407);
            this.labelFinish.Name = "labelFinish";
            this.labelFinish.Size = new System.Drawing.Size(35, 13);
            this.labelFinish.TabIndex = 3;
            this.labelFinish.Text = "label2";
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(311, 407);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(75, 23);
            this.buttonStart.TabIndex = 4;
            this.buttonStart.Text = "Voltar";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // buttonFinish
            // 
            this.buttonFinish.Location = new System.Drawing.Point(691, 407);
            this.buttonFinish.Name = "buttonFinish";
            this.buttonFinish.Size = new System.Drawing.Size(75, 23);
            this.buttonFinish.TabIndex = 5;
            this.buttonFinish.Text = "Voltar";
            this.buttonFinish.UseVisualStyleBackColor = true;
            this.buttonFinish.Click += new System.EventHandler(this.buttonFinish_Click);
            // 
            // panelStep
            // 
            this.panelStep.Location = new System.Drawing.Point(772, 12);
            this.panelStep.Name = "panelStep";
            this.panelStep.Size = new System.Drawing.Size(374, 388);
            this.panelStep.TabIndex = 2;
            // 
            // buttonStep
            // 
            this.buttonStep.Location = new System.Drawing.Point(773, 406);
            this.buttonStep.Name = "buttonStep";
            this.buttonStep.Size = new System.Drawing.Size(75, 23);
            this.buttonStep.TabIndex = 6;
            this.buttonStep.Text = "Avançar";
            this.buttonStep.UseVisualStyleBackColor = true;
            this.buttonStep.Click += new System.EventHandler(this.buttonStep_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1153, 434);
            this.Controls.Add(this.buttonStep);
            this.Controls.Add(this.panelStep);
            this.Controls.Add(this.buttonFinish);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.labelFinish);
            this.Controls.Add(this.labelStart);
            this.Controls.Add(this.panelFinish);
            this.Controls.Add(this.panelStart);
            this.Name = "Form1";
            this.Text = "Morphing";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panelStart;
        private System.Windows.Forms.Panel panelFinish;
        private System.Windows.Forms.Label labelStart;
        private System.Windows.Forms.Label labelFinish;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Button buttonFinish;
        private System.Windows.Forms.Panel panelStep;
        private System.Windows.Forms.Button buttonStep;

    }
}

