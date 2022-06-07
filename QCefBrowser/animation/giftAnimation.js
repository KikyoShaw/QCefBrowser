// const SVGA = require('svgaplayerweb')
class GiftAnimation {
    constructor(option) {
        const defaultOption = {
            list: [],//列表
            autoplay: true,
            loop: false,
            elem: null,//dom
            elemId: "",//
            width: 375,
            height: 672,
            onPlay: function () { }
        }
        this.options = {
            ...defaultOption,
            ...option
        }
        this.list = this.options.list || []
        this.radio = window.devicePixelRatio;
        this.playState = true;//播放中
        this.index = 0; //当前执行动画下标
        this.type = '';//类型
        this.timeout = null; //定时器
        this.getInfo()
        this.init();
    }
    
    getInfo(){//信息
        let obj = this.list[this.index] || {}
        let params = {
            src: obj.carAnimationUrl || obj.webpUrl,
        }
        const newObj = {...obj, ...params}
        this.info = newObj
        this.type = this.getType()
        return newObj
    }

    getType(src){//类型
        src = src || this.info.src
        console.log(src)
        const isWebp = src.slice(-'.webp'.length) == '.webp'
        const isSvga = src.slice(-'.svga'.length) == '.svga'
        const isMp4 = src.slice(-'.mp4'.length) == '.mp4'
        if(isWebp) return 'webp'
        if(isSvga) return 'svga'
        if(isMp4) return 'mp4'
    }

    changeList(list){//数据
        this.list = list
        if(!this.playState){//没在播放就播放下一个
            this.next(true)
        }
    }

    next(reset = false){//播放下一个
        // console.log('播放下一个', this.index)
        if(this.index >= this.list.length -1){
            this.playState = false
            this.remove()
            return;
        }
        this.playState = true
        const preType = this.type
        this.index++
        this.getInfo()
        if(!reset && this.type === preType){//相同类型
            if(this.type === 'mp4'){
                this.video.src = this.info.src
                this.video.currentTime = 0
                this.video.play()
                return;
            }else if(this.type === 'webp'){
                this.webpImg.src = 'data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEHAAEALAAAAAABAAEAAAICTAEAOw=='
                this.webpImg.src = this.info.src
                return;
            }
        }
        !reset && this.remove()
        this.init()
    }

    remove(){
        console.log('remove')
        const elem = this.options.elem
        elem.innerHTML = ''
        try{
            if(this.type === 'mp4'){
                // this.canvas && this.canvas.parentNode.removeChild(this.canvas)
                this.canvas && this.video.parentNode.removeChild(this.video)
                this.video = null
                this.canvas = null
            }else if(this.type === 'webp'){
                // this.webpImg && this.webpImg.parentNode.removeChild(this.webpImg)
                this.webpImg = null
            }else if(this.type === 'svga'){
                if(!this.svgaPlayer) return;
                // const canvas = elem.getElementsByTagName('canvas')[0]
                // elem.removeChild(canvas)
                this.svgaPlayer.clear()
                this.svgaPlayer._videoItem = null
                this.svgaPlayer = null
            }
        }catch(err){}
    }

    destroy(){//销毁
        clearTimeout(this.timeout)
    }

    play() {
        this.playing = true;
        this.video.play();
    }

    pause() {
        this.playing = false;
        this.video.pause();
    }

    init(){
        if(this.type === 'mp4'){
            this.initWebgl()
            this.initVideo()
            if (this.options.autoplay) {
                this.video.play();
            }
        }else if(this.type === 'webp'){
            this.initWebp()
        }else if(this.type === 'svga'){
            this.initSvga()
        }
    }

    initSvga(){
        const id = this.options.elemId
        const svgaPlayer = new SVGA.Player(id);
        svgaPlayer.loops = 1;//动画循环次数，默认值为 0，表示无限循环
        const parser = new SVGA.Parser(id); 
        parser.load(this.info.src, (videoItem) => {
            svgaPlayer.setVideoItem(videoItem);
            svgaPlayer.startAnimation();
            svgaPlayer.onFinished(() => {
                console.log('svg结束')
                this.next()
            });
        }, () => {
            console.log('svg异常')
            this.next()
        })
        this.svgaPlayer = svgaPlayer
    }

    initWebp(){
        const { webpMillis } = this.getInfo()
        const img = document.createElement('img')
        img.src = this.info.src
        img.onload = () => {
            this.timeout = setTimeout(() => {
                console.log('Imgnext')
                this.next()
            }, +webpMillis)
        }
        img.onError = () => {
            console.log('imgError')
            this.next()
        }
        this.options.elem.appendChild(img)
        this.webpImg = img   
    }

    initVideo() {
        const {
            onPlay,
            onError,
            loop,
            src
        } = this.options;

        const video = document.createElement('video');
        video.autoplay = false;
        video.width = this.options.width * 2
        video.height = this.options.height
        // video.mute = true;
        // video.volume = 0;
        // video.muted = true;
        video.loop = loop;
        video.setAttribute('x-webkit-airplay', 'true');
        video.setAttribute('webkit-playsinline', 'true');
        video.setAttribute('playsinline', 'true');
        video.style.display = 'none';
        video.src = this.info.src;
        video.crossOrigin = 'anonymous';
        video.addEventListener('canplay', () => {
            this.playing = true;
            onPlay && onPlay();
        })
        video.addEventListener('error', () => {
            this.next()
        })
        video.addEventListener('play', () => {
            this.frame = window.requestAnimationFrame(() => {
                this.drawFrame();
            });
        })
        video.addEventListener('ended', () => {
            console.log('videoEnd')
            cancelAnimationFrame(this.frame)
            this.playing = false;
            this.next()
        })
        this.video = video;
        document.body.appendChild(video);
    }

    drawFrame() {
        if (this.playing) {
            this.drawWebglFrame();
        }
        this.frame = window.requestAnimationFrame(() => {
            this.drawFrame()
        })
    }

    drawWebglFrame() {
        const gl = this.gl;
        // 配置纹理图像
        gl.texImage2D(
            gl.TEXTURE_2D,
            0,
            gl.RGB,
            gl.RGB,
            gl.UNSIGNED_BYTE,
            this.video
        );
        // 绘制
        gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    }

    initWebgl() {
        this.canvas = document.createElement('canvas');
        this.options.elem.appendChild(this.canvas);
        this.canvas.width = this.options.width * this.radio;
        this.canvas.height = this.options.height * this.radio;
        this.canvas.addEventListener('click', () => {
            this.play();
        });
        const gl = this.canvas.getContext('webgl', {
            antialias: true,
        });
        gl.viewport(
            0,
            0,
            this.options.width * this.radio,
            this.options.height * this.radio
        );

        const program = this._initShaderProgram(gl);
        gl.linkProgram(program);
        gl.useProgram(program);

        const buffer = this._initBuffer(gl);

        // 绑定缓冲
        gl.bindBuffer(gl.ARRAY_BUFFER, buffer.position);
        const aPosition = gl.getAttribLocation(program, 'a_position');
        // 允许属性读取，将缓冲区的值分配给特定的属性
        gl.enableVertexAttribArray(aPosition);

        gl.vertexAttribPointer(aPosition, 2, gl.FLOAT, false, 0, 0);
        gl.bindBuffer(gl.ARRAY_BUFFER, buffer.texture);
        const aTexCoord = gl.getAttribLocation(program, 'a_texCoord');
        gl.enableVertexAttribArray(aTexCoord);
        gl.vertexAttribPointer(aTexCoord, 2, gl.FLOAT, false, 0, 0);

        // 绑定纹理
        const texture = this._initTexture(gl);
        gl.bindTexture(gl.TEXTURE_2D, texture);

        const scaleLocation = gl.getUniformLocation(program, 'u_scale');
        gl.uniform2fv(scaleLocation, [this.radio, this.radio]);

        this.gl = gl;
    }

    _createShader(gl, type, source) {
        const shader = gl.createShader(type);
        gl.shaderSource(shader, source);
        gl.compileShader(shader);
        if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
            console.error(gl.getShaderInfoLog(shader));
        }

        return shader;
    }

    _initShaderProgram(gl) {
        // 顶点着色器glsl代码
        const vsSource = `
        attribute vec2 a_position;
        attribute vec2 a_texCoord;
        varying vec2 v_texCoord;
        uniform vec2 u_scale;
        void main(void) {
            gl_Position = vec4(a_position, 0.0, 1.0);
            v_texCoord = a_texCoord;
        }
        `;
        // // 片元着色器 glsl 代码
        const fsSource = `
        precision lowp float;
        varying vec2 v_texCoord;
        uniform sampler2D u_sampler;
        void main(void) {
            gl_FragColor = vec4(texture2D(u_sampler, v_texCoord+vec2(-0.5, 0)).rgb, texture2D(u_sampler, v_texCoord).r);
        }
        `;
        const vsShader = this._createShader(gl, gl.VERTEX_SHADER, vsSource);
        const fsShader = this._createShader(gl, gl.FRAGMENT_SHADER, fsSource);
        const program = gl.createProgram();
        gl.attachShader(program, vsShader);
        gl.attachShader(program, fsShader);
        gl.linkProgram(program);

        return program;
    }

    _initBuffer(gl) {
        const positionVertice = new Float32Array([
            -1.0, 1.0,
            1.0, 1.0,
            -1.0, -1.0,
            1.0, -1.0
        ]);
        const positionBuffer = gl.createBuffer(); // 创建buffer
        gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer); // 把缓冲区对象绑定到目标
        gl.bufferData(gl.ARRAY_BUFFER, positionVertice, gl.STATIC_DRAW); // 向缓冲区对象写入刚定义的顶点数据

        const textureBuffer = gl.createBuffer();
        const textureVertice = new Float32Array([
            0.5, 1.0,
            1.0, 1.0,
            0.5, 0.0,
            1.0, 0.0
        ]); 
        gl.bindBuffer(gl.ARRAY_BUFFER, textureBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, textureVertice, gl.STATIC_DRAW);

        return {
            position: positionBuffer,
            texture: textureBuffer
        };
    }

    _initTexture(gl) {
        const texture = gl.createTexture();

        gl.bindTexture(gl.TEXTURE_2D, texture);
        // 对纹理图像进行y轴反转，因为WebGL纹理坐标系统的t轴（分为t轴和s轴）的方向和图片的坐标系统Y轴方向相反。因此将Y轴进行反转。
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 1);
        // 配置纹理参数
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);

        return texture;
    }
}

if (typeof module === 'object') {
    module.exports = {
        GiftAnimation: GiftAnimation
    };
}