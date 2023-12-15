//
//  ViewController.swift
//  ffmpeg-demo2
//
//  Created by liuyongchang on 2023/12/6.
//

import Cocoa

class ViewController: NSViewController {

    var recStatus: Bool = false
    let btn = NSButton(title: "开始录制", target: nil, action: nil)
    
    var thread:Thread?
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        self.view.setFrameSize(NSSize(width: 480, height: 480))
       
        btn.frame = NSRect(x: 480/2-80, y: 480/2-80, width: 160, height: 160)
        btn.bezelStyle = .rounded
        btn.action = #selector(sayHi)
        self.view.addSubview(btn)
        
    
        
        
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }

    @objc
    func sayHi() -> Void {
        self.recStatus = !self.recStatus
        if recStatus {
        thread=Thread.init(target: self, selector:#selector(recordCallBack), object: nil)
            btn.title="结束录制"
            thread?.start();
        }else{
            btn.title="开始录制"
            set_status(0);
        }
        
    }
    
    
    @objc
    func recordCallBack() {
        //print("start engin")
        set_status(1);
        rec_audio();
        
    }

}

