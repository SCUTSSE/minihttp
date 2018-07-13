<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。  
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.TextBox2 = New System.Windows.Forms.TextBox()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.TextBox3 = New System.Windows.Forms.TextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("宋体", 20.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.Label1.Location = New System.Drawing.Point(26, 34)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(94, 27)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "ip地址"
        '
        'TextBox1
        '
        Me.TextBox1.Font = New System.Drawing.Font("宋体", 20.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.TextBox1.Location = New System.Drawing.Point(179, 23)
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.Size = New System.Drawing.Size(540, 38)
        Me.TextBox1.TabIndex = 1
        Me.TextBox1.Text = "0.0.0.0"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("宋体", 21.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.Label2.Location = New System.Drawing.Point(31, 98)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(71, 29)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "端口"
        '
        'TextBox2
        '
        Me.TextBox2.Font = New System.Drawing.Font("宋体", 21.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.TextBox2.Location = New System.Drawing.Point(179, 105)
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.Size = New System.Drawing.Size(540, 41)
        Me.TextBox2.TabIndex = 3
        Me.TextBox2.Text = "80"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Font = New System.Drawing.Font("宋体", 21.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.Label3.Location = New System.Drawing.Point(26, 181)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(158, 29)
        Me.Label3.TabIndex = 4
        Me.Label3.Text = "文件夹地址"
        '
        'TextBox3
        '
        Me.TextBox3.Font = New System.Drawing.Font("宋体", 21.5!)
        Me.TextBox3.Location = New System.Drawing.Point(179, 189)
        Me.TextBox3.Name = "TextBox3"
        Me.TextBox3.Size = New System.Drawing.Size(540, 40)
        Me.TextBox3.TabIndex = 5
        Me.TextBox3.Text = "."
        '
        'Button1
        '
        Me.Button1.Font = New System.Drawing.Font("宋体", 21.5!)
        Me.Button1.Location = New System.Drawing.Point(58, 293)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(221, 78)
        Me.Button1.TabIndex = 6
        Me.Button1.Text = "启动"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Font = New System.Drawing.Font("宋体", 21.5!)
        Me.Button2.Location = New System.Drawing.Point(384, 293)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(221, 78)
        Me.Button2.TabIndex = 7
        Me.Button2.Text = "停止"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(800, 450)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.TextBox3)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.TextBox2)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.TextBox1)
        Me.Controls.Add(Me.Label1)
        Me.Name = "Form1"
        Me.Text = "minihttp"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents Label1 As Label
    Friend WithEvents TextBox1 As TextBox
    Friend WithEvents Label2 As Label
    Friend WithEvents TextBox2 As TextBox
    Friend WithEvents Label3 As Label
    Friend WithEvents TextBox3 As TextBox
    Friend WithEvents Button1 As Button
    Friend WithEvents Button2 As Button
End Class
