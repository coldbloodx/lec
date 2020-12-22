
package main

import "net"
import "os"
import "fmt"
import "bytes"

import "github.com/davecgh/go-xdr/xdr2"

type data struct {
    stream    []byte ;
    clusters  string ;
    ncluster  int32    ;
}



func main(){

    fmt.Println("testline\n");

    sock, err := net.Listen("tcp", "192.168.2.138:8080");
    if err != nil {
        fmt.Println(err);
        defer sock.Close();
        os.Exit(-1);
    }

    for {
        conn, err := sock.Accept();

        if err != nil {
            fmt.Println(err);
            defer sock.Close();
            os.Exit(-1);
        }

        fmt.Fprintln(conn, "Hello from TCP server");

        var buf [1000]byte;
        nbytes, err := conn.Read(buf[0:1000]);

        fmt.Printf("read %d bytes\n", nbytes);
        fmt.Printf("buf: %+v\n", buf);

        var mydata data;

        decoder := xdr.NewDecoder(bytes.NewReader(buf[0:1000]));
        
        aaa, _, err := decoder.DecodeOpaque();
        bbb, _, err := decoder.DecodeString();
        ccc, _, err := decoder.DecodeUint();  

        if err != nil {
            fmt.Println(err);
            defer sock.Close();
            os.Exit(-1);
        }
        
        fmt.Printf("aaa: %+v\n", aaa);
        fmt.Printf("bbb: %+v\n", bbb);
        fmt.Printf("ccc: %+v\n", ccc);

        decoder1 := xdr.NewDecoder(bytes.NewReader(buf[0:1000]));


        mydata.stream, _, err = decoder1.DecodeOpaque();
        mydata.clusters, _, err = decoder1.DecodeString();
        mydata.ncluster, _, err = decoder1.DecodeInt();  

        fmt.Printf("mydata: %+v\n", mydata);
        
        var mydata1 data;
        ncount, err := xdr.Unmarshal(bytes.NewReader(buf[0:1000]), &mydata1);
        //bytesRead, err := xdr.Unmarshal(bytes.NewReader(encodedData), &h)

        if err != nil {
            fmt.Println(err);
            defer sock.Close();
            os.Exit(-1);
        }
        fmt.Printf("mydata1: %+v, ncount: %d\n", mydata1, ncount);
        


        



    }

    os.Exit(0);
}
