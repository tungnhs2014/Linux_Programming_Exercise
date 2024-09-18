# exercise 4 for process

- Viết một chương trình A tạo ra hai tiến trình con B và C. Ở tiến trình B, C tạo tiến trình con B’, C’. Thực hiện ghi nội dung “Hello I’m B process” 
( Đối với tiến trình B và tương tự với các process còn lại) theo thứ tự B’-> C’ -> B -> C vào file. Ở tiến trình A, dùng waitpid()
để xác định xem khi nào B kết thúc thì ghi vào file.
