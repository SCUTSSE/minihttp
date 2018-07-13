Public Class Form1
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Shell("minihttp.exe --address " + TextBox1.Text + " --port " + TextBox2.Text + " --docroot " + TextBox3.Text)
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Shell("cmd.exe /c taskkill /f /im minihttp.exe")

    End Sub
End Class
