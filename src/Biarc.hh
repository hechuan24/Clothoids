/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2017                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                |
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

///
/// file: Biarc.hh
///

#ifndef BIARC_HH
#define BIARC_HH

#include "G2lib.hh"
#include "Circle.hh"

//! Clothoid computations routine
namespace G2lib {

  /*\
   |   ____  _
   |  | __ )(_) __ _ _ __ ___
   |  |  _ \| |/ _` | '__/ __|
   |  | |_) | | (_| | | | (__
   |  |____/|_|\__,_|_|  \___|
  \*/

  /*!
   * \brief Compute biarc fitting by Hemite data
   *
   */

  class Biarc : public BaseCurve {
    CircleArc m_C0, m_C1;

    void
    gfun( real_type alpha, real_type g[3] ) const {
      real_type so  = sin(alpha);
      real_type co  = cos(alpha);
      real_type oco = alpha*co;
      g[0] = so + oco;
      g[1] = 2*co - alpha*so;
      g[2] = -3*so - oco;
    }

  public:

    #include "BaseCurve_using.hxx"

    virtual
    ~Biarc() UTILS_OVERRIDE
    {}

    //explicit
    Biarc()
    : BaseCurve(G2LIB_BIARC)
    {}

    //explicit
    Biarc( Biarc const & ba )
    : BaseCurve(G2LIB_BIARC)
    { copy(ba); }

    //! construct a clothoid with the standard parameters
    explicit
    Biarc(
      real_type x0,
      real_type y0,
      real_type theta0,
      real_type x1,
      real_type y1,
      real_type theta1
    )
    : BaseCurve(G2LIB_BIARC)
    {
      bool ok = build( x0, y0, theta0, x1, y1, theta1 );
      UTILS_ASSERT(
        ok,
        "Biarc( x0={}, y0={}, theta0={}, x1={}, y1={}, theta1={}) cannot be computed\n",
        x0, y0, theta0, x1, y1, theta1
      );
    }

    explicit
    Biarc( BaseCurve const & C );

    void
    copy( Biarc const & c ) {
      m_C0.copy(c.m_C0);
      m_C1.copy(c.m_C1);
    }

    Biarc const & operator = ( Biarc const & ba )
    { copy(ba); return *this; }

    CircleArc const & C0() const { return m_C0; }
    CircleArc const & C1() const { return m_C1; }

    //! construct a biarc with the standard parameters
    bool
    build(
      real_type x0,
      real_type y0,
      real_type theta0,
      real_type x1,
      real_type y1,
      real_type theta1
    );

    /*!
     *  \brief
     *  construct a biarc by 3 point at "minimum energy"
     *  - Planar point set fairing and fitting by arc splines
     *  - Xunnian Yang and Guozhao Wang
     *  - Computer-Aided Design, vol 33, 2001
     */
    bool
    build_3P(
      real_type x0,
      real_type y0,
      real_type x1,
      real_type y1,
      real_type x2,
      real_type y2
    );

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    virtual
    void
    bbox(
      real_type & xmin,
      real_type & ymin,
      real_type & xmax,
      real_type & ymax
    ) const UTILS_OVERRIDE;

    virtual
    void
    bbox_ISO(
      real_type   offs,
      real_type & xmin,
      real_type & ymin,
      real_type & xmax,
      real_type & ymax
    ) const UTILS_OVERRIDE;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    virtual
    real_type
    length() const UTILS_OVERRIDE
    { return m_C0.length()+m_C1.length(); }

    virtual
    real_type
    length_ISO( real_type offs ) const UTILS_OVERRIDE
    { return m_C0.length_ISO(offs)+m_C1.length_ISO(offs); }

    virtual
    real_type
    thetaBegin() const UTILS_OVERRIDE
    { return m_C0.thetaBegin(); }

    virtual
    real_type
    thetaEnd() const UTILS_OVERRIDE
    { return m_C1.thetaEnd(); }

    virtual
    real_type
    xBegin() const UTILS_OVERRIDE
    { return m_C0.xBegin(); }

    virtual
    real_type
    xEnd() const UTILS_OVERRIDE
    { return m_C1.xEnd(); }

    virtual
    real_type
    yBegin() const UTILS_OVERRIDE
    { return m_C0.yBegin(); }

    virtual
    real_type
    yEnd() const UTILS_OVERRIDE
    { return m_C1.yEnd(); }

    virtual
    real_type
    tx_Begin() const UTILS_OVERRIDE
    { return m_C0.tx_Begin(); }

    virtual
    real_type
    tx_End() const UTILS_OVERRIDE
    { return m_C1.tx_End(); }

    virtual
    real_type
    ty_Begin() const UTILS_OVERRIDE
    { return m_C0.ty_Begin(); }

    virtual
    real_type
    ty_End() const UTILS_OVERRIDE
    { return m_C1.ty_End(); }

    virtual
    real_type
    nx_Begin_ISO() const UTILS_OVERRIDE
    { return m_C0.nx_Begin_ISO(); }

    virtual
    real_type
    nx_End_ISO() const UTILS_OVERRIDE
    { return m_C1.nx_End_ISO(); }

    virtual
    real_type
    ny_Begin_ISO() const UTILS_OVERRIDE
    { return m_C0.ny_Begin_ISO(); }

    virtual
    real_type
    ny_End_ISO() const UTILS_OVERRIDE
    { return m_C1.ny_End_ISO(); }

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    virtual
    real_type
    theta( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    theta_D( real_type ) const UTILS_OVERRIDE;

    virtual
    real_type
    theta_DD( real_type ) const UTILS_OVERRIDE
    { return 0; }

    virtual
    real_type
    theta_DDD( real_type ) const UTILS_OVERRIDE
    { return 0; }

    virtual
    void
    evaluate(
      real_type   s,
      real_type & th,
      real_type & k,
      real_type & x,
      real_type & y
    ) const UTILS_OVERRIDE;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    virtual real_type X( real_type s ) const UTILS_OVERRIDE;
    virtual real_type Y( real_type s ) const UTILS_OVERRIDE;

    virtual real_type X_D( real_type ) const UTILS_OVERRIDE;
    virtual real_type Y_D( real_type ) const UTILS_OVERRIDE;

    virtual real_type X_DD( real_type ) const UTILS_OVERRIDE;
    virtual real_type Y_DD( real_type ) const UTILS_OVERRIDE;

    virtual real_type X_DDD( real_type ) const UTILS_OVERRIDE;
    virtual real_type Y_DDD( real_type ) const UTILS_OVERRIDE;

    virtual real_type X_ISO( real_type s, real_type offs ) const UTILS_OVERRIDE;
    virtual real_type Y_ISO( real_type s, real_type offs ) const UTILS_OVERRIDE;

    virtual real_type X_ISO_D( real_type, real_type offs ) const UTILS_OVERRIDE;
    virtual real_type Y_ISO_D( real_type, real_type offs ) const UTILS_OVERRIDE;

    virtual real_type X_ISO_DD( real_type, real_type offs ) const UTILS_OVERRIDE;
    virtual real_type Y_ISO_DD( real_type, real_type offs ) const UTILS_OVERRIDE;

    virtual real_type X_ISO_DDD( real_type, real_type offs ) const UTILS_OVERRIDE;
    virtual real_type Y_ISO_DDD( real_type, real_type offs ) const UTILS_OVERRIDE;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    virtual
    void
    eval(
      real_type   s,
      real_type & x,
      real_type & y
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_D(
      real_type   s,
      real_type & x_D,
      real_type & y_D
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_DD(
      real_type   s,
      real_type & x_DD,
      real_type & y_DD
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_DDD(
      real_type   s,
      real_type & x_DDD,
      real_type & y_DDD
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_ISO(
      real_type   s,
      real_type   offs,
      real_type & x,
      real_type & y
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_ISO_D(
      real_type   s,
      real_type   offs,
      real_type & x_D,
      real_type & y_D
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_ISO_DD(
      real_type   s,
      real_type   offs,
      real_type & x_DD,
      real_type & y_DD
    ) const UTILS_OVERRIDE;

    virtual
    void
    eval_ISO_DDD(
      real_type   s,
      real_type   offs,
      real_type & x_DDD,
      real_type & y_DDD
    ) const UTILS_OVERRIDE;

    /*\
     |  _____                   _   _   _
     | |_   _|   __ _ _ __   __| | | \ | |
     |   | |    / _` | '_ \ / _` | |  \| |
     |   | |   | (_| | | | | (_| | | |\  |
     |   |_|    \__,_|_| |_|\__,_| |_| \_|
    \*/

    virtual
    real_type
    tx( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    tx_D( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    tx_DD( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    tx_DDD( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    ty( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    ty_D( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    ty_DD( real_type s ) const UTILS_OVERRIDE;

    virtual
    real_type
    ty_DDD( real_type s ) const UTILS_OVERRIDE;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    virtual
    void
    tg(
      real_type   s,
      real_type & tx,
      real_type & ty
    ) const UTILS_OVERRIDE;

    virtual
    void
    tg_D(
      real_type   s,
      real_type & tx_D,
      real_type & ty_D
    ) const UTILS_OVERRIDE;

    virtual
    void
    tg_DD(
      real_type   s,
      real_type & tx_DD,
      real_type & ty_DD
    ) const UTILS_OVERRIDE;

    virtual
    void
    tg_DDD(
      real_type   s,
      real_type & tx_DDD,
      real_type & ty_DDD
    ) const UTILS_OVERRIDE;

    /*\
     |  _                        __
     | | |_ _ __ __ _ _ __  ___ / _| ___  _ __ _ __ ___
     | | __| '__/ _` | '_ \/ __| |_ / _ \| '__| '_ ` _ \
     | | |_| | | (_| | | | \__ \  _| (_) | |  | | | | | |
     |  \__|_|  \__,_|_| |_|___/_|  \___/|_|  |_| |_| |_|
    \*/

    virtual
    void
    translate( real_type tx, real_type ty ) UTILS_OVERRIDE
    { m_C0.translate(tx,ty); m_C1.translate(tx,ty); }

    virtual
    void
    rotate( real_type angle, real_type cx, real_type cy ) UTILS_OVERRIDE
    { m_C0.rotate(angle,cx,cy); m_C1.rotate(angle,cx,cy); }

    virtual
    void
    reverse() UTILS_OVERRIDE;

    virtual
    void
    changeOrigin( real_type newx0, real_type newy0 ) UTILS_OVERRIDE;

    virtual
    void
    trim( real_type s_begin, real_type s_end ) UTILS_OVERRIDE;

    virtual
    void
    scale( real_type s ) UTILS_OVERRIDE;

    /*\
     |        _                     _   ____       _       _
     |    ___| | ___  ___  ___  ___| |_|  _ \ ___ (_)_ __ | |_
     |   / __| |/ _ \/ __|/ _ \/ __| __| |_) / _ \| | '_ \| __|
     |  | (__| | (_) \__ \  __/\__ \ |_|  __/ (_) | | | | | |_
     |   \___|_|\___/|___/\___||___/\__|_|   \___/|_|_| |_|\__|
    \*/

    virtual
    int_type
    closestPoint_ISO(
      real_type   qx,
      real_type   qy,
      real_type & x,
      real_type & y,
      real_type & s,
      real_type & t,
      real_type & dst
    ) const UTILS_OVERRIDE;

    virtual
    int_type
    closestPoint_ISO(
      real_type   qx,
      real_type   qy,
      real_type   offs,
      real_type & x,
      real_type & y,
      real_type & s,
      real_type & t,
      real_type & dst
    ) const UTILS_OVERRIDE;

    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    real_type xMiddle()     const { return m_C1.xBegin(); }
    real_type yMiddle()     const { return m_C1.yBegin(); }
    real_type thetaMiddle() const { return m_C1.thetaBegin(); }
    real_type kappa0()      const { return m_C0.curvature(); }
    real_type length0()     const { return m_C0.length(); }
    real_type kappa1()      const { return m_C1.curvature(); }
    real_type length1()     const { return m_C1.length(); }

    real_type delta_theta() const { return m_C0.delta_theta() + m_C1.delta_theta(); }

    void
    bbTriangles(
      std::vector<Triangle2D> & tvec,
      real_type                 max_angle = Utils::m_pi/18,
      real_type                 max_size  = 1e100,
      int_type                  icurve    = 0
    ) const {
      m_C0.bbTriangles( tvec, max_angle, max_size, icurve );
      m_C1.bbTriangles( tvec, max_angle, max_size, icurve );
    }

    void
    bbTriangles_ISO(
      real_type                 offs,
      std::vector<Triangle2D> & tvec,
      real_type                 max_angle = Utils::m_pi/18,
      real_type                 max_size  = 1e100,
      int_type                  icurve    = 0
    ) const {
      m_C0.bbTriangles_ISO( offs, tvec, max_angle, max_size, icurve );
      m_C1.bbTriangles_ISO( offs, tvec, max_angle, max_size, icurve );
    }

    void
    bbTriangles_SAE(
      real_type                 offs,
      std::vector<Triangle2D> & tvec,
      real_type                 max_angle = Utils::m_pi/18,
      real_type                 max_size  = 1e100,
      int_type                  icurve    = 0
    ) const {
      m_C0.bbTriangles_SAE( offs, tvec, max_angle, max_size, icurve );
      m_C1.bbTriangles_SAE( offs, tvec, max_angle, max_size, icurve );
    }

    /*\
     |             _ _ _     _
     |    ___ ___ | | (_)___(_) ___  _ __
     |   / __/ _ \| | | / __| |/ _ \| '_ \
     |  | (_| (_) | | | \__ \ | (_) | | | |
     |   \___\___/|_|_|_|___/_|\___/|_| |_|
    \*/

    bool
    collision( Biarc const & B ) const {
      return m_C0.collision( B.m_C0 ) || m_C0.collision( B.m_C1 ) ||
             m_C1.collision( B.m_C0 ) || m_C1.collision( B.m_C1 );
    }

    bool
    collision_ISO(
      real_type     offs,
      Biarc const & B,
      real_type     offs_B
    ) const {
      return m_C0.collision_ISO( offs, B.m_C0, offs_B ) ||
             m_C0.collision_ISO( offs, B.m_C1, offs_B ) ||
             m_C1.collision_ISO( offs, B.m_C0, offs_B ) ||
             m_C1.collision_ISO( offs, B.m_C1, offs_B );
    }

    /*\
     |   _       _                          _
     |  (_)_ __ | |_ ___ _ __ ___  ___  ___| |_
     |  | | '_ \| __/ _ \ '__/ __|/ _ \/ __| __|
     |  | | | | | ||  __/ |  \__ \  __/ (__| |_
     |  |_|_| |_|\__\___|_|  |___/\___|\___|\__|
    \*/

    void
    intersect(
      Biarc const   & B,
      IntersectList & ilist,
      bool            swap_s_vals
    ) const;

    void
    intersect_ISO(
      real_type       offs,
      Biarc const   & B,
      real_type       offs_B,
      IntersectList & ilist,
      bool            swap_s_vals
    ) const;

    void
    info( ostream_type & stream ) const UTILS_OVERRIDE
    { stream << "BiArc\n" << *this << '\n'; }

    friend
    ostream_type &
    operator << ( ostream_type & stream, Biarc const & bi );

  };

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  build_guess_theta(
    int_type        n,
    real_type const x[],
    real_type const y[],
    real_type       theta[]
  );

}

#endif

///
/// eof: Biarc.hh
///
