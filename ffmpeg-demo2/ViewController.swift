//
//  ViewController.swift
//  ffmpeg-demo2
//
//  Created by liuyongchang on 2023/12/6.
//

import Cocoa

class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        self.view.setFrameSize(NSSize(width: 480, height: 480))
        let btn = NSButton(title: "Hello Ffmpeg", target: nil, action: nil)
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
        print("Hello FFmpeg")
        hello_ffmpeg()
        
    }

}

