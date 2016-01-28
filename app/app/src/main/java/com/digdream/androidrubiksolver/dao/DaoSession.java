package com.digdream.androidrubiksolver.dao;

import android.database.sqlite.SQLiteDatabase;

import java.util.Map;

import de.greenrobot.dao.AbstractDao;
import de.greenrobot.dao.AbstractDaoSession;
import de.greenrobot.dao.identityscope.IdentityScopeType;
import de.greenrobot.dao.internal.DaoConfig;

// THIS CODE IS GENERATED BY greenDAO, DO NOT EDIT.

/**
 * {@inheritDoc}
 * 
 * @see de.greenrobot.dao.AbstractDaoSession
 */
public class DaoSession extends AbstractDaoSession {

    private final DaoConfig solveDaoConfig;

    private final SolveDao solveDao;

    public DaoSession(SQLiteDatabase db, IdentityScopeType type, Map<Class<? extends AbstractDao<?, ?>>, DaoConfig>
            daoConfigMap) {
        super(db);

        solveDaoConfig = daoConfigMap.get(SolveDao.class).clone();
        solveDaoConfig.initIdentityScope(type);

        solveDao = new SolveDao(solveDaoConfig, this);

        registerDao(Solve.class, solveDao);
    }
    
    public void clear() {
        solveDaoConfig.getIdentityScope().clear();
    }

    public SolveDao getSolveDao() {
        return solveDao;
    }

}