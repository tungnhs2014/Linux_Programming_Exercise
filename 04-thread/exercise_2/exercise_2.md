# Exercise 2 for thread

- Viết một chương trình thực hiện tạo 3 threads. 
- hread thứ nhất thực hiện việc nhập dữ liệu sinh viên từ bàn phím, bao gồm thông tin: Họ tên, ngày sinh, quê quán.
- Mỗi lần nhập xong dữ liệu một sinh viên, thread thứ hai sẽ ghi thông tin sinh viên đó vào file (mỗi thông tin sinh viên nằm trên 1 dòng) thongtinsinhvien.txt. 
- Thread thứ 3 sẽ đọc dữ liệu vừa ghi được và in ra terminal rồi thông báo cho thread 1 tiếp tục nhập thêm sinh viên.
- Sử dụng mutex và condition variable để giải quyết bài toán.
