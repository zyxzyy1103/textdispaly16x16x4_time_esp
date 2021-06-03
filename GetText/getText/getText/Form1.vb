Public Class Form1
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Dim wid As Integer = PictureBox1.ClientSize.Width
        Dim hgt As Integer = PictureBox1.ClientSize.Height
        Dim bm As New Bitmap(wid, hgt)
        Dim gr As Graphics = Graphics.FromImage(bm)

        gr.FillRectangle(Brushes.Blue, 0, 0, 50, 50)

        PictureBox1.Image = bm
        PictureBox1.Refresh()

        gr.Dispose()
    End Sub
End Class
